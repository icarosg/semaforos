#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// definição dos pinos dos LEDs
#define LED_R 13
#define LED_G 11
#define LED_B 12

// função para inicializar os LEDs
void init_hardware(void)
{
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 1); // começa com o vermelho aceso

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);
}

// função de callback do timer para alternar as cores do semáforo
bool repeating_timer_callback(struct repeating_timer *t)
{
    if (gpio_get(LED_R))
    {                       // se o vermelho está aceso
        gpio_put(LED_R, 0); // apaga vermelho
        gpio_put(LED_B, 1); // acende amarelo
    }
    else if (gpio_get(LED_B))
    {                       // se o amarelo está aceso
        gpio_put(LED_B, 0); // apaga amarelo
        gpio_put(LED_G, 1); // acende verde
    }
    else if (gpio_get(LED_G))
    {                       // se o verde está aceso
        gpio_put(LED_G, 0); // apaga verde
        gpio_put(LED_R, 1); // acende vermelho
    }
    return true; // continua repetindo o timer
}

int main()
{
    stdio_init_all();
    init_hardware();

    // configura um timer para disparar a cada 3000ms (3 segundos)
    struct repeating_timer timer;
    add_repeating_timer_ms(-3000, repeating_timer_callback, NULL, &timer);

    int segundos = 0;

    // loop principal
    while (true)
    {
        printf("Tempo decorrido: %d segundos\n", segundos);
        sleep_ms(1000);
    }
}
