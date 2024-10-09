#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int cs_fd, sc_fd;
    char buffer[96];

    printf("Digite uma string: ");
    fgets(buffer, 1024, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  

    cs_fd = open("FIFO_CS", O_WRONLY);
    write(cs_fd, buffer, strlen(buffer) + 1);
    close(cs_fd);

    sc_fd = open("FIFO_SC", O_RDONLY);
    read(sc_fd, buffer, sizeof(buffer));
    close(sc_fd);

    printf("Resposta do servidor: %s\n", buffer);

    return 0;
}
