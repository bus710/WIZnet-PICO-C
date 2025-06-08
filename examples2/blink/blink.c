// /**
//  * Copyright (c) 2021 WIZnet Co.,Ltd
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Includes
//  * ----------------------------------------------------------------------------------------------------
//  */
// #include <stdio.h>
//
// #include "port_common.h"
//
// #include "wizchip_conf.h"
// #include "wizchip_spi.h"
//
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Macros
//  * ----------------------------------------------------------------------------------------------------
//  */
// /* Clock */
// #define PLL_SYS_KHZ (133 * 1000)
//
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Variables
//  * ----------------------------------------------------------------------------------------------------
//  */
// /* Network */
// static wiz_NetInfo g_net_info =
//     {
//         .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
//         .ip = {192, 168, 11, 2},                     // IP address
//         .sn = {255, 255, 255, 0},                    // Subnet Mask
//         .gw = {192, 168, 11, 1},                     // Gateway
//         .dns = {8, 8, 8, 8},                         // DNS server
// #if _WIZCHIP_ > W5500
//         .lla = {0xfe, 0x80, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x02, 0x08, 0xdc, 0xff,
//                 0xfe, 0x57, 0x57, 0x25},             // Link Local Address
//         .gua = {0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00},             // Global Unicast Address
//         .sn6 = {0xff, 0xff, 0xff, 0xff,
//                 0xff, 0xff, 0xff, 0xff,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00},             // IPv6 Prefix
//         .gw6 = {0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00},             // Gateway IPv6 Address
//         .dns6 = {0x20, 0x01, 0x48, 0x60,
//                 0x48, 0x60, 0x00, 0x00,
//                 0x00, 0x00, 0x00, 0x00,
//                 0x00, 0x00, 0x88, 0x88},             // DNS6 server
//         .ipmode = NETINFO_STATIC_ALL
// #else
//         .dhcp = NETINFO_STATIC        
// #endif
// };
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Functions
//  * ----------------------------------------------------------------------------------------------------
//  */
// /* Clock */
// static void set_clock_khz(void);
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Main
//  * ----------------------------------------------------------------------------------------------------
//  */
// int main()
// {
//     /* Initialize */
//     uint8_t link_status;
//     wiz_PhyConf phyconf;
//     uint16_t count = 0;
//
//     set_clock_khz();
//
//     stdio_init_all();
//     sleep_ms(3000);
//     wizchip_spi_initialize();
//     wizchip_cris_initialize();
//
//     wizchip_reset();
//     wizchip_initialize();
//     wizchip_check();
//
//     network_initialize(g_net_info);
//
//     /* Get network information */
//     print_network_information(g_net_info);
//
//     /* Infinite loop */
//     do
//     {
//         link_status = wizphy_getphylink();
//         printf("%u", link_status);
//         if (link_status == PHY_LINK_OFF)
//         {
//             count++;
//             if (count > 10)
//             {
//                 printf("Link failed of Internal PHY.\r\n");
//                 break;
//             }
//         }
//         sleep_ms(500);
//
//     } while (link_status == PHY_LINK_OFF);
//
//     if (link_status == PHY_LINK_ON)
//     {
//         wizphy_getphyconf(&phyconf);
//         printf("Link OK of Internal PHY.\r\n");
//         printf("the %d Mbtis speed of Internal PHY.\r\n", phyconf.speed == PHY_SPEED_10 ? 100 : 10);
//         printf("The %s Duplex Mode of the Internal PHY.\r\n", phyconf.duplex == PHY_DUPLEX_FULL ? "Full-Duplex" : "Half-Duplex");
//
//         printf("\r\nTry ping the ip:%d.%d.%d.%d.\r\n", g_net_info.ip[0], g_net_info.ip[1], g_net_info.ip[2], g_net_info.ip[3]);
//     }
//     else
//     {
//         printf("\r\nPlease check whether the network cable is loose or disconnected.\r\n");
//     }
//     while (1)
//     {
//         ;
//     }
// }
//
// /**
//  * ----------------------------------------------------------------------------------------------------
//  * Functions
//  * ----------------------------------------------------------------------------------------------------
//  */
// /* Clock */
// static void set_clock_khz(void)
// {
//     // set a system clock frequency in khz
//     set_sys_clock_khz(PLL_SYS_KHZ, true);
//
//     // configure the specified clock
//     clock_configure(
//         clk_peri,
//         0,                                                // No glitchless mux
//         CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, // System PLL on AUX mux
//         PLL_SYS_KHZ * 1000,                               // Input frequency
//         PLL_SYS_KHZ * 1000                                // Output (must be same as no divider)
//     );
// }
//
#include <stdio.h>
#include "pico/stdlib.h"

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
