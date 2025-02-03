#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

// Definindo os pinos dos LEDs e o botão
const uint led_pin_azul = 11; 
const uint led_pin_vermelho = 12;
const uint led_pin_verde = 13;
const uint botaoA = 5;

// Variável para controlar a ativação do LED
volatile bool led_sequence_active = false;

// Funções de callback para desligar os LEDs
bool turn_off_azul(alarm_id_t id, void *user_data) { // Desligar o LED verde
    gpio_put(led_pin_verde, 0);
    led_sequence_active = false;  // Permitir nova ativação pelo botão
    return false;
}

bool turn_off_vermelho(alarm_id_t id, void *user_data) { // Desligar o LED vermelho
    gpio_put(led_pin_vermelho, 0); 
    add_alarm_in_ms(3000, (alarm_callback_t)turn_off_azul, NULL, false); // Temporizador
    return false;
}

bool turn_off_verde(alarm_id_t id, void *user_data) { // Desligar o LED azul
    gpio_put(led_pin_azul, 0);
    add_alarm_in_ms(3000, (alarm_callback_t)turn_off_vermelho, NULL, false); // Temporizador
    return false;
}

// Função de callback para o botão
void button_callback(uint gpio, uint32_t events) {
    // Verifica se a sequência de LEDs está ativa 
    if (!led_sequence_active) { 
        led_sequence_active = true; // Impede que a sequência seja ativada novamente
        // Aciona os LEDs
        gpio_put(led_pin_azul, 1); 
        gpio_put(led_pin_vermelho, 1);
        gpio_put(led_pin_verde, 1);
        add_alarm_in_ms(3000, (alarm_callback_t)turn_off_verde, NULL, false); // Temporizador
    }
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial

    // Inicializa os pinos dos LEDs e do botão
    gpio_init(led_pin_azul);
    gpio_set_dir(led_pin_azul, GPIO_OUT);
    gpio_init(led_pin_vermelho);
    gpio_set_dir(led_pin_vermelho, GPIO_OUT);
    gpio_init(led_pin_verde);
    gpio_set_dir(led_pin_verde, GPIO_OUT);
    gpio_init(botaoA);
    gpio_set_dir(botaoA, GPIO_IN);
    gpio_pull_up(botaoA);


    while (true) {
        // Adiciona um callback para o botão
        gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_RISE, true, &button_callback);
        sleep_ms(1000);
    }
}