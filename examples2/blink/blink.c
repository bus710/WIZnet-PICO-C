// #include <stdio.h>
// #include "pico/stdlib.h"

#include "port_common.h"
//
// #include "wizchip_conf.h"
// #include "wizchip_spi.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

#undef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 19

// Perform initialisation
int pico_led_init(void) {
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
}

int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    while (true) {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}
