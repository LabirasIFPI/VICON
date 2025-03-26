#include <stdio.h>
#include "pico/stdlib.h"    
#include "hardware/uart.h"
#include "utils/wifi/wifi.h"
#include "utils/server/server.h"
#include "utils/display/display.h"

int main() {
    stdio_init_all();
    inicializar_display();
    conectar_wifi();
    start_server();

    return 0;
}