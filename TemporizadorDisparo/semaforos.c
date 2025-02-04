#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// definição dos pinos
#define LED_R 13
#define LED_G 11
#define LED_B 12
#define BOTAO_A 5

// variáveis globais
bool em_execucao = false;


// callback's para desligar os LEDs em sequência
int64_t turn_off_led1_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_R, 0);
    return 0;
}

int64_t turn_off_led2_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, 0);
    return 0;
}

int64_t turn_off_led3_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_G, 0);
    em_execucao = false;  // permite nova ativação pelo botão
    return 0;
}

// inicializar hardware
void init_hardware(void) {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
}

// inicia a sequência dos LEDs com timers de 3 segundos entre estados
void iniciar_sequencia_leds() {
    if (!em_execucao) {  // só inicia se não houver uma sequência ativa
        em_execucao = true;

        // liga todos os LEDs inicialmente
        gpio_put(LED_R, 1);
        gpio_put(LED_G, 1);
        gpio_put(LED_B, 1);

        // alarmes para desligar os LEDs sequencialmente
        add_alarm_in_ms(3000, turn_off_led1_callback, NULL, false);
        add_alarm_in_ms(6000, turn_off_led2_callback, NULL, false);
        add_alarm_in_ms(9000, turn_off_led3_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();
    init_hardware();

    while (true) {
        if (!gpio_get(BOTAO_A)) {  // botão pressionado
            iniciar_sequencia_leds();
            sleep_ms(300);
        }
        sleep_ms(10);
    }
}
