import socket
import time

# Definição do endereço IP e da porta do servidor
TCP_IP = '10.0.0.129'  # IP do servidor (localhost)
TCP_PORT = 5000  # Porta do servidor
BUFFER_SIZE = 1024  # Tamanho máximo do buffer para recebimento de dados


def start_server():
    # Criação do socket TCP/IP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # AF_INET indica IPv4, SOCK_STREAM indica TCP

    try:
        server_socket.connect((TCP_IP, TCP_PORT))
        print("Conectado ao Raspberry Pi Pico!")
        return server_socket

    except Exception as e:
        print("Falha na conexão:", e)


# Descomente a função abaixo para permitir envio de dados para o cliente
def send_data(server_socket, data):
    try:
        message = f'{data}'  # Dados que você deseja enviar
        # Envia a mensagem para o servidor (o Raspberry Pi Pico no caso)
        server_socket.send(message.encode())
    

        # Recebe a resposta do servidor (se necessário)
        response =  server_socket.recv(1024)
        print("Resposta do servidor:", response.decode())

    except Exception as e:
        print("Erro ao enviar dados:", e)