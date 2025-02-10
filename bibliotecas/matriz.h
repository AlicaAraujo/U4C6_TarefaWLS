#ifndef MATRIZ_H
#define MATRIZ_H

#include "hardware/pio.h"

//Definindo pino para matriz e o número de pixels da mesma
#define PIN_LED_MATRIZ 7
#define NUM_PIXELS 25

extern const uint32_t desenhoNum[10][25];

//Função que inicializa a matriz
uint matriz_init(uint pin_out);

//Função que desenha o número na matriz
void desenhaNumero(uint8_t numero);

#endif