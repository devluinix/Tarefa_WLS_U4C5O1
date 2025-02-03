#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

int estado = 0;

// Função que alterna os LEDs
bool alternar_leds(struct repeating_timer *t)
{
    // Desliga todos os LEDs
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Acende o LED vermelho, depois o verde e o amarelo
    if (estado == 0)
    {
        gpio_put(LED_VERMELHO, 1); // Acende o LED vermelho
    }
    else if (estado == 1)
    {
        gpio_put(LED_AMARELO, 1); // Acende o LED amarelo
    }
    else if (estado == 2)
    {
        gpio_put(LED_VERDE, 1); // Acende o LED verde
    }

    estado = estado + 1; // Alterna entre 0, 1 e 2
    if (estado > 2)
    {
        estado = 0;
    }

    return true; // Retorna true para continuar o temporizador
}

int main()
{
    stdio_init_all();

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configura do temporizador mostrado na aula, configurado para 3s
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, alternar_leds, NULL, &timer);

    while (true)
    {
        // Texto pra ficar mostrando no terminal
        printf("Semaforo em execução %d\n", estado);
        sleep_ms(1000); // Mantém o microcontrolador em execução
    }
}