#ifndef BOTAO_H
#define BOTAO_H

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Declaração do manipulador de interrupção (caso não esteja declarado em outro lugar)
extern void gpio_irq_handler(uint gpio, uint32_t events);

// Definição do pino do botão
#define BOTAO_A 5
#define BOTAO_B 6

void inicializaBotao();
extern void gpio_irq_handler(uint gpio, uint32_t eventos);

#endif // BOTAO_H
