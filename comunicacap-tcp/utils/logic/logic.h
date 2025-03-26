#ifndef LOGIC_H
#define LOGIC_H

#include "stdio.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"
#include "utils/buzzer/buzzer.h"
int qtd_pessoas(int  u_encontrado, int  d_encontrado,int valor_u, int valor_d){
    if((u_encontrado) || (d_encontrado)){
        return valor_u - valor_d;
    }
    return 0;
}

void processar_dados(struct pbuf *p) {
    if (p == NULL) {
        printf("Erro\n");
        return;
    }

    // Usar buffer direto para evitar cópia desnecessária
    char *buffer = (char *)p->payload;
    int valor_u = 0, valor_d = 0;
    int u_encontrado = 0, d_encontrado = 0;
    char *ptr = buffer;

    // Simplificando a análise dos dados manualmente
    while (*ptr != '\0') {
        if (*ptr == 'u') {
            ptr++; // Avança para o valor após 'u'
            valor_u = atoi(ptr); // Extrai o número após 'u'
            u_encontrado = 1;
        } else if (*ptr == 'd') {
            ptr++; // Avança para o valor após 'd'
            valor_d = atoi(ptr); // Extrai o número após 'd'
            d_encontrado = 1;
        }
        ptr++;
    }

    int qtd_local = qtd_pessoas(u_encontrado, d_encontrado, valor_u, valor_d);
    if (qtd_local >= 0) {
        if (qtd_local > 2) {
            printf("Número de pessoas acima da capacidade\n");
            ativabuzzer();
        } else {
            printf("Número de pessoas normais\n");
        }
    }
}

#endif