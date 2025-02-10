#include "leds.h"

// Função que inicializa o pino do LED e configura como saída
void led_init(uint gpio) {
    gpio_init(gpio); // Inicializa o LED
    gpio_set_dir(gpio, GPIO_OUT); // Configura o LED como saída
}

// Função responsável por ligar o LED
void ligaLed(uint gpio) {
    gpio_put(gpio, 1);
}

// Função responsável por desligar o LED
void desligaLed(uint gpio) {
    gpio_put(gpio, 0);
}

void inicializaLEDs() {
    // Inicializando os pinos dos LEDs
    //led_init(LED_VERMELHO);
    led_init(LED_AZUL);
    led_init(LED_VERDE);
}