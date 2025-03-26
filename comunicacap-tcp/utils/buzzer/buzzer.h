#ifndef SERVER_H
#define SERVER_H

#include "pico/stdlib.h"

// Definindo o pino do buzzer
#define BUZZER_PIN 21

// Frequências das notas (em Hz)
#define D4 294    // D (Ré)
#define F4 349    // F (Fá)
#define A4 440    // A (Lá)
#define C4 262    // C (Dó)
#define E4 330    // E (Mi)
#define G4 392    // G (Sol)
#define Bb4 466   // Bb (Si bemol)
#define C5 523    // C (Dó)

#define NOTE_DURATION 400  // Duração das notas (em ms)

void play_note(uint pin, uint frequency, uint duration_ms) {
    uint half_period_us = 1000000 / frequency / 2;  // Meio período em microssegundos
    uint end_time = time_us_32() + duration_ms * 1000;

    while (time_us_32() < end_time) {
        gpio_put(pin, 1);  // Ligando o pino (emitindo som)
        sleep_us(half_period_us);  // Espera metade do período
        gpio_put(pin, 0);  // Desligando o pino (pausa)
        sleep_us(half_period_us);  // Espera a outra metade do período
    }
}

void ativarBuzzer() {
    stdio_init_all();

    // Configura o pino do buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Parte do "Nós vai descer" (Refrão)
    while (true) {
        // Dm (Ré menor)
        play_note(BUZZER_PIN, D4, NOTE_DURATION);  // D (Ré)
        play_note(BUZZER_PIN, F4, NOTE_DURATION);  // F (Fá)
        play_note(BUZZER_PIN, A4, NOTE_DURATION);  // A (Lá)
        sleep_ms(200);  // Pausa entre os acordes

        // C (Dó maior)
        play_note(BUZZER_PIN, C4, NOTE_DURATION);  // C (Dó)
        play_note(BUZZER_PIN, E4, NOTE_DURATION);  // E (Mi)
        play_note(BUZZER_PIN, G4, NOTE_DURATION);  // G (Sol)
        sleep_ms(200);  // Pausa entre os acordes

        // Bb (Si bemol maior)
        play_note(BUZZER_PIN, Bb4, NOTE_DURATION);  // Bb (Si bemol)
        play_note(BUZZER_PIN, D4, NOTE_DURATION);  // D (Ré)
        play_note(BUZZER_PIN, F4, NOTE_DURATION);  // F (Fá)
        sleep_ms(200);  // Pausa entre os acordes

        // A (Lá maior)
        play_note(BUZZER_PIN, A4, NOTE_DURATION);  // A (Lá)
        play_note(BUZZER_PIN, C5, NOTE_DURATION);  // C (Dó)
        play_note(BUZZER_PIN, E4, NOTE_DURATION);  // E (Mi)
        sleep_ms(200);  // Pausa entre os acordes

        sleep_ms(500);  // Pausa entre as repetições do refrão

        // Repetir a sequência ou adicionar mais partes, conforme desejado
    }
}

#endif