/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 15:01:37 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
int	g_exit_status;

int	init_shell(t_data *shell, char **env)
{
	shell->env_list = init_env(env);
	if (shell->env_list == NULL)
		return (EXIT_FAILURE);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_pid = -2;
	shell->infile_fd = -2;
	shell->outfile_fd = -2;
	shell->pipe_fd[0] = -2;
	shell->pipe_fd[1] = -2;
	shell->exit_status = 0;
	shell->heredoc = NULL;
	shell->old_stdin = -1;
	return (EXIT_SUCCESS);
}

int	minishell_loop(t_data *shell)
{
	while (1)
	{
		ignore_signals();
		shell->user_line = readline(PROMPT);
		if (g_exit_status == 130)
		{
			shell->exit_status = 130;
			g_exit_status = 0;
		}
		if (!shell->user_line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			free_and_exit(shell, shell->exit_status);
		}
		if (lexer(shell) == EXIT_SUCCESS && parser(shell) == EXIT_SUCCESS)
			g_exit_status = executer(shell);
		else
			g_exit_status = 1;
		free_data(shell);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (check_args(argc) || init_shell(&data, env))
		free_and_exit(NULL, EXIT_FAILURE);
	minishell_loop(&data);
	free_and_exit(&data, data.exit_status);
	return (0);
}
