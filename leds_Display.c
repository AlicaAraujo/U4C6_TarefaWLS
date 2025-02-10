/*
    Autor (a): Alícia Oliveira Araújo
    U4C6 - TarefaWLS - Aula Síncrona do dia 03/02/2025
    Última modificação: 09/02/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"
#include "botao.h"
#include "leds.h"
#include "animacoes.h"
#include "matriz.h"
#include "ssd1306.h"
#include "font.h"

#define endereco 0x3C      // Endereço I2C do display OLED
#define I2C_PORT i2c1      // Porta I2C utilizada
#define PIN_SDA 14         // Pino SDA do I2C
#define PIN_SCL 15         // Pino SCL do I2C

// Variáveis globais
uint8_t cont = 0;           // Contador para exibição de números
bool led_verde_status = false; // Estado do LED verde
bool led_azul_status = false;  // Estado do LED azul
absolute_time_t debounce;      // Controle de debounce dos botões
ssd1306_t display;             // Estrutura do display OLED

// Função para exibir mensagens no display OLED
void exibirNoDisplay(const char *msg) {
    ssd1306_fill(&display, false);  // Limpa o display antes de escrever
    ssd1306_draw_string(&display, msg, 8, 10);
    ssd1306_send_data(&display);
}

// Função para processar entrada de caracteres e exibir no display/matriz
void getCaractere(char c) {
    char str[2] = {c, '\0'};  // Converte caractere em string
    exibirNoDisplay(str);      // Exibe no display

    // Se for número, exibe na matriz de LEDs
    if (c >= '0' && c <= '9') {
        desenhaNumero(c - '0');
    } 
    // Exibir caracteres alfanuméricos no display
    else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        exibirNoDisplay(str);
    } 
    // Exibir caracteres especiais no display
    else if (c >= 32 && c <= 126) {
        exibirNoDisplay(str);
    } 
    // Caso o caractere não seja suportado
    else {
        printf("Caractere inválido!\n");
        exibirNoDisplay("Inválido");
    }
}

// Tratamento de interrupção para os botões
void gpio_irq_handler(uint gpio, uint32_t eventos) {
    if (time_reached(debounce)) {  // Verifica debounce
        debounce = delayed_by_ms(get_absolute_time(), 200);  // Aplica debounce

        if (gpio == BOTAO_A) {  // Botão A pressionado
            if (led_azul_status) {  
                led_azul_status = false;
                gpio_put(LED_AZUL, 0);
            }
            led_verde_status = !led_verde_status;  // Alterna estado do LED verde
            gpio_put(LED_VERDE, led_verde_status);
            printf("Botão A pressionado: 🟢 LED verde %s\n", led_verde_status ? "ligado 💡 ." : "desligado ⚫ .");
            exibirNoDisplay(led_verde_status ? "LED verde ligado" : "LED verde desligado");
        } 
        else if (gpio == BOTAO_B) {  // Botão B pressionado
            if (led_verde_status) {  
                led_verde_status = false;
                gpio_put(LED_VERDE, 0);
            }
            led_azul_status = !led_azul_status;  // Alterna estado do LED azul
            gpio_put(LED_AZUL, led_azul_status);
            printf("Botão B pressionado: 🔵 LED azul %s\n", led_azul_status ? "ligado 💡 ." : "desligado ⚫ .");
            exibirNoDisplay(led_azul_status ? "LED azul ligado" : "LED azul desligado");
        }
    }
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    sleep_ms(2000);    // Aguarda estabilização do sistema

    // Configuração dos botões e LEDs
    inicializaBotao();
    inicializaLEDs();

    // Configuração das interrupções nos botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Inicializa a matriz de LEDs
    matriz_init(7);
    desenhaNumero(cont);

    // Configuração do barramento I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);

    // Inicializa e configura o display OLED
    sleep_ms(100);
    ssd1306_init(&display, 128, 64, false, endereco, I2C_PORT);
    ssd1306_config(&display);
    ssd1306_send_data(&display);

    ssd1306_fill(&display, false);  // Limpa o display
    ssd1306_send_data(&display);

    // Configura debounce inicial
    debounce = delayed_by_ms(get_absolute_time(), 200);

    // Loop principal: Lê caracteres via UART e exibe no display
    while (true) {
        char c;
        if (scanf("%c", &c) == 1) {
            printf("Caractere recebido: %c.\n", c);
            getCaractere(c);
        }
        sleep_ms(50);  // Pequeno delay para evitar sobrecarga da CPU
    }
}
