/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 16:29:42 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
int	g_exit_status;

int	init_shell(t_data *data, char **env)
{
	data->env = init_env(env);
	if (data->env == NULL)
		return (EXIT_FAILURE);
	data->exit_status = 0;
	data->heredoc = NULL;
	data->stdin_old = -1;
	data->tokens = NULL;
	data->commands = NULL;
	data->prev_pid = -2;
	data->infile_fd = -2;
	data->outfile_fd = -2;
	data->pipe_fd[0] = -2;
	data->pipe_fd[1] = -2;
	return (EXIT_SUCCESS);
}

int	minishell_loop(t_data *data)
{
	while (1)
	{
		signals_handler();
		data->user_line = readline(PROMPT);
		if (g_exit_status == 130)
		{
			data->exit_status = 130;
			g_exit_status = 0;
		}
		if (!data->user_line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 5);
			ft_free_all_and_exit(data, data->exit_status);
		}
		if (lexer(data) == EXIT_SUCCESS && parsing(data) == EXIT_SUCCESS)
			g_exit_status = executing(data);
		else
			g_exit_status = 1;
		ft_free_all(data);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (check_args(argc) || init_shell(&data, env))
		ft_free_all_and_exit(NULL, EXIT_FAILURE);
	minishell_loop(&data);
	ft_free_all_and_exit(&data, data.exit_status);
	return (0);
}
