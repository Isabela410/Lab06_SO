#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void LetrasEmMaiusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int cs_fd, sc_fd;
    char buffer[96];

    if (access("FIFO_CS", F_OK) == 0) {
        unlink("FIFO_CS");
    }
    if (mkfifo("FIFO_CS", S_IWUSR | S_IRUSR) != 0){ //Cria FIFO 1
        puts("Erro ao criar a FIFO 1, poxa!");
        return -1;
    }
    puts("FIFO 1 criada com sucesso, oba!");

    if (access("FIFO_SC", F_OK) == 0) {
        unlink("FIFO_SC");
    }
    
    if (mkfifo("FIFO_SC", S_IWUSR | S_IRUSR) != 0){ //Cria FIFO 2
        puts("Erro ao criar a FIFO 2, poxa!");
        return -1;
    }
    puts("FIFO 2 criada com sucesso, oba!");

    while (1) {
        cs_fd = open("FIFO_CS", O_RDONLY);
        read(cs_fd, buffer, sizeof(buffer));
        close(cs_fd);

        LetrasEmMaiusculo(buffer);

        sc_fd = open("FIFO_SC", O_WRONLY);
        write(sc_fd, buffer, strlen(buffer) + 1);
        close(sc_fd);
    }

    unlink("FIFO_CS");
    unlink("FIFO_SC");

    return 0;
}
