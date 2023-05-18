#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipeFD[2]; // aici is file descriptori pt pipe.. meaning cel de pe poz 0 e pt read si cel de pe 1 pt write
    pid_t pid; // process id ul pt noul proces creat
    char message[] = "Buna siua si bine v-am regasit la un nou episod";

    if (pipe(pipeFD) == -1) { // functia pipe creeaza un pipe si ii asigneaza file descriptori
        perror("Failed to create pipe!");
        return 1;
    }

    pid = fork(); // fork creeaza un child process din procesul principal

    if (pid == -1) {
        perror("Error creating the process!");
        return 1;
    }

    if (pid == 0) {
        // partea asta e pentru child process
        close(pipeFD[0]);// aici inchidem partea de read a pipe ului
        write(pipeFD[1], message, strlen(message) + 1); // write ataseaza mesajul la partea de write
        close(pipeFD[1]);// aici inchidem partea de write a pipe ului
        return 0;
    } else {
        // iar asta pentru parent process
        //same ca si mai sus
        close(pipeFD[1]);
        char received_message[strlen(message) + 1];
        read(pipeFD[0], received_message, sizeof(received_message));
        printf("Received message: %s\n", received_message);
        close(pipeFD[0]);
        return 0;
    }
}
