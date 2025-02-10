<h1 align="center">Interrupções, Matriz de LEDs e Display OLED ⚠️ 🟥🟩🟦🟨</h1>

<h2 align="center">Descrição do Projeto 📝</h2>

Este repositório foi desenvolvido para demonstrar a utilização do microcontrolador RP2040 e da placa BitDogLab, aplicando conceitos de interrupções, comunicação serial e controle de hardware em sistemas embarcados. O projeto foi criado como parte de uma tarefa prática da EmbarcaTech, residência de Sistemas Embarcados.

<h2 align="center">Objetivo da Tarefa 🎯</h2>

A tarefa consiste na construção de um programa para controlar os seguintes componentes:

- **Matriz 5x5 de LEDs WS2812** conectada à GPIO 7.
- **LED RGB** com os pinos conectados às GPIOs 11, 12 e 13.
- **Botão A** conectado à GPIO 5.
- **Botão B** conectado à GPIO 6.
- **Display OLED SSD1306** conectado via I2C (GPIOs 14 e 15).

<h2 align="center">Funcionalidades Implementadas ⚡</h2>

- O **botão A** alterna o estado do LED verde e exibe uma mensagem no display OLED e no Serial Monitor.
- O **botão B** alterna o estado do LED azul e exibe uma mensagem no display OLED e no Serial Monitor.
- Entrada de caracteres via **Serial Monitor**:
  - Quando um caractere é digitado, ele é exibido no display OLED.
  - Se um número entre 0 e 9 for digitado, ele será exibido também na matriz 5x5 de LEDs.
- O **debounce** foi implementado para evitar leituras errôneas dos botões.
- Todas as funcionalidades dos botões foram implementadas utilizando **interrupções (IRQ)**.
- Modificação na biblioteca `font.h` para adicionar caracteres minúsculos ao display OLED.

<h2 align="center">Estrutura do Projeto 📚</h2>

O projeto está organizado da seguinte forma (descrição dos arquivos principais 📂):

- **`animacoes.c/h`**: Contém os padrões dos números que serão exibidos na matriz 5x5.
- **`botao.c/h`**: Configuração e inicialização dos botões.
- **`interrupcoes.c/h`**: Configuração das interrupções nos botões.
- **`leds.c/h`**: Inicializa e controla os LEDs RGB.
- **`matriz.c/h`**: Configuração da matriz de LEDs WS2812 e exibição de números.
- **`ssd1306.c/h`**: Controle do display OLED SSD1306 via protocolo I2C.
- **`leds_Display.c`**: Arquivo principal que gerencia a interação entre botões, display e matriz de LEDs.
- **`font.h`**: Biblioteca de fontes customizadas para o display OLED.
- **`tarefaWLS.pio`**: Código PIO para controle dos LEDs WS2812.

<h2 align="center">Como Executar 🖥️</h2>

### Requisitos:
- Placa **BitDogLab** ou **Raspberry Pi Pico**.
- VS Code com extensão **Pico-W C/C++**.
- Simulador **Wokwi** (opcional).

### Passos:

1. Clone este repositório para sua máquina local:
   ```bash
   git clone https://github.com/SeuUsuario/tarefaWLS.git
   ```
2. Abra o projeto no VS Code.
3. Conecte a placa BitDogLab em modo BOOTSEL.
4. Compile e execute o projeto na placa.

<h2 align="center">Demonstração/Execução 📹</h2>

Confira o vídeo com a execução desta tarefa na placa BitDogLab:

[Assista ao vídeo]()

<h2 align="center">📅 Informações</h2>

📌 Autor(a): Alícia Oliveira Araújo
📅 Data da Aula: 03/02/2025
🛠 Última Modificação do Código: 09/02/2025

Projeto desenvolvido como parte da Residência de Sistemas Embarcados - EmbarcaTech.

