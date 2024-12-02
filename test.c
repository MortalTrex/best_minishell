#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void execute_command(char *cmd, int input_fd, int output_fd) {
    if (input_fd != 0) { // Si l'entrée standard n'est pas stdin
        dup2(input_fd, STDIN_FILENO); // Rediriger input_fd vers stdin
        close(input_fd);
    }
    if (output_fd != 1) { // Si la sortie standard n'est pas stdout
        dup2(output_fd, STDOUT_FILENO); // Rediriger output_fd vers stdout
        close(output_fd);
    }
    // Remplacer le processus courant par la commande
    execlp(cmd, cmd, NULL); // Remplace le processus avec la commande `cmd`
    perror("execlp failed"); // Si execlp échoue
    exit(EXIT_FAILURE);
}

int main() {
    int pipes[2][2]; // Deux pipes pour connecter les 3 commandes
    int status;
    pid_t pid;

    // Tableau des commandes
    char *commands[3] = {"ls", "ls", "ls"};

    for (int i = 0; i < 3; i++) {
        // Créer un pipe si ce n'est pas la dernière commande
        if (i < 2 && pipe(pipes[i % 2]) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }

        // Créer un processus enfant
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Processus enfant
            if (i > 0) { 
                // Si ce n'est pas la première commande, connecter stdin au pipe précédent
                close(pipes[(i - 1) % 2][1]); // Fermer l'extrémité écriture du pipe précédent
                execute_command(commands[i], pipes[(i - 1) % 2][0], (i < 2) ? pipes[i % 2][1] : 1);
            } else {
                // Si c'est la première commande, stdin est par défaut et stdout va au pipe
                execute_command(commands[i], 0, pipes[i % 2][1]);
            }
        } else { // Processus parent
            if (i > 0) close(pipes[(i - 1) % 2][0]); // Fermer l'extrémité lecture du pipe précédent
            if (i < 2) close(pipes[i % 2][1]); // Fermer l'extrémité écriture du pipe actuel
        }
    }

    // Attendre la fin de tous les processus enfants
    for (int i = 0; i < 3; i++) {
        wait(&status);
    }
	
    return 0;
}
