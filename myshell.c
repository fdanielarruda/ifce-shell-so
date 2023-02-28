#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TRUE 1
#define MAX_LINE 80
#define MAX_PARAMS 10

int status;
char* params[MAX_PARAMS];
char line[MAX_LINE];

void type_prompt() {
    printf("$ ");
}

void read_command(char* params[]) {
    fflush(stdout);

    fgets(line, MAX_LINE, stdin);

    int i = 0;
    params[i] = strtok(line, " \n");

    while (params[i] != NULL) {
        i++;
        params[i] = strtok(NULL, " \n");
    }

    params[i] = NULL;
}

// EXECUÇÃO DO PROGRAMA
int main() {  
    // LOOP INFINITO
    while(TRUE) {
        type_prompt(); // EXIBE O PROMPT
        read_command(params); // ENTRADA DO TECLADO

        // exit FINALIZA O SHELL
        if (strcmp(params[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork(); // CRIA UM PROCESSO FILHO

        // VALIDAÇÃO DE POSSÍVEL ERRO NA EXECUÇÃO
        if (pid < 0) {
            printf("Erro ao realizar o fork.\n");
            continue;
        }

        if (pid != 0) {
            waitpid(-1, &status, 0); // PAI ESPERA O FILHO
        } else {
            execvp(params[0], params); // FILHO EXECUTA O COMANDO
            fprintf(stderr, "Erro ao executar o comando.\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}