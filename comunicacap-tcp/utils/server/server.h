#ifndef SERVER_H
#define SERVER_H

#include "stdio.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"
#include "utils/logic/logic.h"

#define PORT 5000

static struct tcp_pcb *server_pcb;
// Função chamada quando os dados são recebidos
static err_t on_receive(void *arg, struct tcp_pcb *client_pcb, struct pbuf *p, err_t err) {
    if (p != NULL) {
        // Exibir dados recebidos
        printf("Recebido: %.*s\n", p->len, (char *)p->payload);
        //Processar dados enviados
        processar_dados(p);
        // Enviar resposta ao cliente
        tcp_write(client_pcb, "Mensagem recebida!", 18, TCP_WRITE_FLAG_COPY);
        tcp_output(client_pcb);

        // Liberar o buffer de recebimento
        pbuf_free(p);
    } else if (err == ERR_OK) {
        // Cliente fechou a conexão
        tcp_close(client_pcb);
    }
    return ERR_OK;
}

// Função chamada quando há uma nova conexão
static err_t on_connect(void *arg, struct tcp_pcb *client_pcb, err_t err) {
    printf("Cliente conectado!\n");

    // Configurar callback de recebimento
    tcp_recv(client_pcb, on_receive);
    return ERR_OK;
}

void start_server() {
    stdio_init_all();
    // Criar controle do servidor
    server_pcb = tcp_new();
    tcp_bind(server_pcb, IP_ADDR_ANY, PORT);
    server_pcb = tcp_listen(server_pcb);

    // Configurar callback de conexão
    tcp_accept(server_pcb, on_connect);

    printf("Servidor iniciado na porta %d\n", PORT);
}
#endif
