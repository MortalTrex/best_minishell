/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/04 18:23:57 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

/* static void	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	copy_env(envp, data);
	data->exit_status = 0;
	data->pipe_fd[0] = dup(STDIN_FILENO);
	data->pipe_fd[1] = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &data->terminal);
} */
static void init_minishell(t_data *data, char **envp) {
    // Initialize environment variables
    data->env = NULL; // Populate this with your environment variables
    data->envc = NULL; // Populate this with your environment variable count
    data->tok = NULL; // Initialize token list
    data->user_line = NULL; // Initialize user input line
    data->exit_status = 0; // Reset exit status
    data->last_pid = 0; // Reset last PID
    data->wstatus = 0; // Reset wait status
    data->heredoc = 0; // Reset heredoc counter
	ft_memset(data, 0, sizeof(t_data));
	copy_env(envp, data);
    // Set up terminal attributes
    struct termios term;
    tcgetattr(STDIN_FILENO, &term); // Get current terminal attributes
    data->terminal = term; // Save original terminal settings

    // Optionally, set up other signals like SIGTSTP (Ctrl+Z)
}
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_minishell(&data, envp);
	while (true)
	{
		signals(&data);
		data.free_value = 0;
		data.user_line = readline(PROMPT);
		if ((*data.user_line))
			add_history(data.user_line);
		if (data.user_line == NULL)
		{
			ft_printf("Exit\n");
			break ;
		}
		if (!ft_tokenize(&data))
			continue ;
		//print_tokens(&data);
		parse_tokens(&data);
		if (data.parsing_error)
		{
			ft_parsing_error(&data);
			continue ;
		}
		//ft_execution(&data);
		execute_ast(data.ast, &data);
		data.free_value = 1;
		ft_free_all(&data);
	}
	data.free_value = 0;
	ft_free_all(&data);
	return (data.exit_status);
}
