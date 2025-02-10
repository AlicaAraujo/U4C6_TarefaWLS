#include "botao.h"

//extern void gpio_irq_handler(uint gpio, uint32_t eventos);

// Função que inicializa o pino do botão e configura como entrada com resistores pull-up
void botao_init(uint gpio) {
    gpio_init(gpio); // Inicializa o botão 
    gpio_set_dir(gpio, GPIO_IN); // Configura botão como entrada
    gpio_pull_up(gpio); // Habilita o pull-up interno do botão
}

void inicializaBotao(uint gpio) {
    //Inicializando o botão A
    botao_init(BOTAO_A);
    //Inicializando o botão B
    botao_init(BOTAO_B);
}