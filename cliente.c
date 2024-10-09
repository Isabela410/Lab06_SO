#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <FIFO cliente_para_servidor> <FIFO servidor_para_cliente>\n", argv[0]);
        exit(1);
    }

    const char* fifo_cliente_para_servidor = argv[1];
    const char* fifo_servidor_para_cliente = argv[2];

    mkfifo(fifo_cliente_para_servidor, 0666);
    mkfifo(fifo_servidor_para_cliente, 0666);

    char buffer[BUFFER_SIZE];

    printf("Digite uma string para enviar ao servidor: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    int fd_cliente_para_servidor = open(fifo_cliente_para_servidor, O_WRONLY);
    write(fd_cliente_para_servidor, buffer, strlen(buffer) + 1);
    close(fd_cliente_para_servidor);

    int fd_servidor_para_cliente = open(fifo_servidor_para_cliente, O_RDONLY);
    read(fd_servidor_para_cliente, buffer, BUFFER_SIZE);
    close(fd_servidor_para_cliente);

    printf("Resposta do servidor: %s\n", buffer);

    return 0;
}
