#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

void converter_para_maiusculas(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

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
    int fd_cliente_para_servidor, fd_servidor_para_cliente;

    while (1) {
        fd_cliente_para_servidor = open(fifo_cliente_para_servidor, O_RDONLY);
        read(fd_cliente_para_servidor, buffer, BUFFER_SIZE);
        close(fd_cliente_para_servidor);

        printf("Servidor recebeu: %s\n", buffer);

        converter_para_maiusculas(buffer);

        fd_servidor_para_cliente = open(fifo_servidor_para_cliente, O_WRONLY);
        write(fd_servidor_para_cliente, buffer, strlen(buffer) + 1);
        close(fd_servidor_para_cliente);

        printf("Servidor enviou: %s\n", buffer);
    }

    return 0;
}
