#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "utils/display/display.h"

#define led_rgb_red 13                  // Define o pino 13 como o pino do LED vermelho.
#define led_rgb_green 11 
#define WIFI_SSID "MALUCO LOBERA"
#define WIFI_PASSWORD "16out1962"
#define PORT 5000

int conectar_wifi(){
    stdio_init_all();

    
    gpio_init(led_rgb_green);          // Inicializa o pino do LED verde (pino 11).
    gpio_set_dir(led_rgb_green, GPIO_OUT);  // Define o pino do LED verde como saída (para acender/desligar o LED).

    gpio_init(led_rgb_red);            // Inicializa o pino do LED vermelho (pino 13).
    gpio_set_dir(led_rgb_red, GPIO_OUT);
    
    // Inicializar Wi-Fi
    if (cyw43_arch_init()) {
        printf("Falha ao inicializar o Wi-Fi\n");
        return -1;
    }

    // Conectar ao Wi-Fi
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Falha ao conectar ao Wi-Fi\n");
        gpio_put(led_rgb_red, 1);
        return -1;
    }

    gpio_put(led_rgb_green, 1);
    printf("Conectado ao Wi-Fi!\n");
    uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
    // exibir_texto(ip_addresstext);
    char ip_string[30]; // Buffer para armazenar a string do IP
    sprintf(ip_string, "%d.%d.%d.%d", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    char informacoes[64];
    sprintf(informacoes,"%s | %d", ip_string, PORT);
    exibir_texto(informacoes);
    printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);

    // Loop principal
    while (true) {
        cyw43_arch_poll();
    }

}

#endif