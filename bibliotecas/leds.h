#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"

// Definição dos pinos dos LEDs
#define LED_VERDE   11
#define LED_AZUL    12
#define LED_VERMELHO 13

void inicializaLEDs();
void ligaLed(uint gpio);
void desligaLed(uint gpio);

#endif // LEDS_H
