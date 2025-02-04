# README - Controle de LEDs com Raspberry Pi Pico

## Descrição
Este projeto implementa o controle de três LEDs (azul, vermelho e verde) utilizando um Raspberry Pi Pico. Os LEDs são ativados ao pressionar um botão e desligam em uma sequência temporizada. 

## Componentes Necessários
- Raspberry Pi Pico
- 3 LEDs (azul, vermelho e verde)
- 3 resistores (recomendado: 330Ω)
- 1 botão push
- Jumpers para conexão
- Placa de ensaio (breadboard)

## Esquema de Conexão
- LED Azul: Pino GP11
- LED Vermelho: Pino GP12
- LED Verde: Pino GP13
- Botão: Pino GP5 (com pull-up interno ativado)

## Como Funciona
1. Ao pressionar o botão, os três LEDs são acesos simultaneamente.
2. Um temporizador é ativado para desligar os LEDs em sequência:
   - Após 3 segundos, o LED azul desliga.
   - Após mais 3 segundos, o LED vermelho desliga.
   - Após mais 3 segundos, o LED verde desliga.
3. O sistema impede que a sequência seja reiniciada enquanto os LEDs ainda estão ativos.

## Como Compilar e Executar
1. Instale o SDK do Raspberry Pi Pico conforme a documentação oficial: [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
2. Clone este repositório e navegue até o diretório do projeto.
3. Compile o código utilizando CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Copie o arquivo `.uf2` gerado para o Raspberry Pi Pico:
   - Conecte o Pico ao computador segurando o botão BOOTSEL.
   - Monte-o como uma unidade de armazenamento USB.
   - Arraste o arquivo `.uf2` para a unidade montada.
5. O código será executado automaticamente após o upload.

## Dependências
- Raspberry Pi Pico SDK
- Biblioteca `pico/stdlib.h`
- Biblioteca `hardware/gpio.h`
- Biblioteca `pico/time.h`

## Autor
- Ylo Silva de Sá Bittencourt