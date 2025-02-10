#include "interrupcoes.h"
#include "hardware/gpio.h"
#include "bibliotecas/botao.h"

// Função responsável por configurar as interrupções nos botões
void interrupcoes() {
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}
