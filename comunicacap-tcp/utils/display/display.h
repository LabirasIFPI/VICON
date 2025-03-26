#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "hardware/i2c.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // Endereço I2C do display
#define I2C_SDA 14           // Pino SDA
#define I2C_SCL 15           // Pino SCL

// Instância do display
static ssd1306_t display;

// Função para inicializar o display
static inline void inicializar_display() {
    i2c_init(i2c1, 400 * 1000); // Inicializa I2C (400 kHz)
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    if (!ssd1306_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ADDRESS, i2c1)) {
        printf("Falha ao inicializar o display SSD1306\n");
    }
}

// Função para exibir texto no display
static inline void exibir_texto(const char *texto) {
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, 0, 0, 1, texto);
    ssd1306_show(&display);
}

#endif // DISPLAY_H
