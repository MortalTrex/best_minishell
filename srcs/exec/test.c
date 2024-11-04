#include "minishell.h"

static void execute_command(t_ast_node *node, t_data *data);
static void handle_redirection(t_redir *redir);
static void handle_heredoc(t_redir *redir);
static void restore_std_fds(int saved_stdin, int saved_stdout);

static void handle_redirection(t_redir *redir) {
    while (redir) {
        int fd;
        if (redir->type == IN) {
            fd = open(redir->file, O_RDONLY);
            if (fd < 0) {
                perror("open IN redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        } else if (redir->type == OUT) {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open OUT redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (redir->type == D_APPEND) {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("open D_APPEND redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        } else if (redir->type == D_HEREDOC) {
            handle_heredoc(redir);
            dup2(redir->hd_fd, STDIN_FILENO); // Redirect stdin to heredoc
        }
        redir = redir->next;
    }
}

static void handle_heredoc(t_redir *redir) {
    int pipe_fd[2];
    char *buffer;
    size_t len = 0;

    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe in the parent process
    close(pipe_fd[1]);

    // Signal handler for SIGINT to prevent hanging on input
    signal(SIGINT, SIG_DFL);

    while (1) {
        buffer = NULL;
        len = 0;

        // Read input until the delimiter is reached
        printf("> "); // Prompt for heredoc input
        getline(&buffer, &len, stdin);

        // Check for delimiter
        if (strcmp(buffer, redir->file) == 0) {
            free(buffer);
            break; // Exit if the delimiter is matched
        }

        // Write the input to the pipe
        write(pipe_fd[1], buffer, strlen(buffer));
        free(buffer);
    }

    // Close the write end of the pipe
    close(pipe_fd[1]);

    // Set the fd in redir structure to the read end of the pipe
    redir->hd_fd = pipe_fd[0];
}

static void restore_std_fds(int saved_stdin, int saved_stdout) {
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

static void execute_command(t_ast_node *node, t_data *data) {
    if (!node) return;
	if (!node || !node->command) return;

    // Print command and arguments for debugging
    printf("Executing command: %s\n", node->command);
    for (int i = 0; node->argv && node->argv[i] != NULL; i++) {
        printf("arg[%d]: %s\n", i, node->argv[i]);
    }

    // Save original stdin and stdout
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    // Handle redirections
    if (node->redir) {
        handle_redirection(node->redir);
    }

    // Fork the process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execve(ft_path(node->argv[0], data), node->argv, data->envc) == -1) {
            perror("execvp failed");
            (ft_free_all(data), exit(EXIT_FAILURE));
        }
    } else {
        // Parent process
        waitpid(pid, &data->wstatus, 0);
        data->exit_status = WEXITSTATUS(data->wstatus);
    }

    // Restore standard file descriptors
    restore_std_fds(saved_stdin, saved_stdout);

    // Recursively execute left and right children for piped commands
    if (node->left) {
        execute_command(node->left, data);
    }
    if (node->right) {
        execute_command(node->right, data);
    }
}

void execute_ast(t_ast_node *ast, t_data *data) {
    if (ast) {
        execute_command(ast, data);
    }
}
