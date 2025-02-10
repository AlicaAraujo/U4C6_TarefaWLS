#include "matriz.h"
#include "animacoes.h"
#include "hardware/clocks.h"
#include "leds_Display.pio.h"

// Declaração de variáveis globais
static PIO pio = pio0;
static uint sm = 0;

//Função responsável pela inicialização da matriz
uint matriz_init(uint pin_out) {
    set_sys_clock_khz(133000, false); // Configura o clock para 133 MHz

    // Configurações da PIO
    uint offset = pio_add_program(pio, &leds_Display_program);
    sm = pio_claim_unused_sm(pio, true);
    leds_Display_program_init(pio, sm, offset, pin_out);

    //Retorna a máquina de estado usada
    return sm;
}

// Função para definir a intensidade das cores do LED
uint32_t matrix_rgb(double r, double g, double b) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (R << 16) | (G << 8) | (B); 
}

// Função que calcula o índice de um LED em uma matriz 5x5, levando em consideração a disposição das linhas
// (alternando a direção da esquerda para a direita) dependendo se a linha é par ou ímpar. 
int getIndex(int num) {
    int x = num % 5;    
    int y = num / 5;    
  
    if (y % 2 == 0)
      return y * 5 + x; 
    else 
      return y * 5 + (4 - x); 
  }

// Função para acionar a matriz de LEDs WS2812B
void acionaMatriz(const uint32_t *desenho, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led;
        
        // Calcula o índice correto de cada LED na matriz
        int index = getIndex(i);

        // Se o LED faz parte do número, acende na cor azul bebê
        if (desenho[24 - index] == 1) {
            valor_led = matrix_rgb(r, g, b); // Azul bebê
        } else {
            valor_led = matrix_rgb(0, 0, 0); // Cor preta (desligado)
        }

        // Envia o valor para a matriz de LEDs
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função responsável por desenhar um número na matriz de LEDs
void desenhaNumero(uint8_t numero) {
    const uint32_t *desenho = desenhoNum[numero];
    double cores[10][3] = {
        {1.0, 0.0, 0.0}, // Vermelho
        {0.0, 1.0, 0.0}, // Verde
        {1.0, 0.0, 1.0}, // Rosa
        {0.0, 1.0, 1.0}, // Ciano
        {1.0, 1.0, 0.0}, // Amarelo
        {1.0, 0.0, 1.0}, // Magenta
        {0.0, 1.0, 1.0}, // Ciano
        {1.0, 0.5, 0.0}, // Laranja
        {0.5, 0.0, 1.0}, // Roxo
        {0.5, 1.0, 0.0}  // Verde-limão
    };
    acionaMatriz(desenho, pio, sm, cores[numero][0], cores[numero][1], cores[numero][2]);
}