/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/25 12:32:44 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
int		g_exit_status;

void	ft_readline(t_data *data)
{
	data->heredoc = 0;
	data->isinfile = 0;
	data->isoutfile = 0;
	signal(SIGINT, sigint_handler);
	data->user_line = readline(PROMPT);
	if (data->user_line)
		add_history(data->user_line);
	data->stdin_old = -1;
	data->exit_status = 0;
	data->heredoc = NULL;
	// if (data->user_line == NULL)
	// {
	// 	ft_printf("Exit\n");
	// 	ft_free_all(data);
	// 	exit(0);
	// }
}
int	init_data(t_data *data, char **env)
{
	data->tokens = NULL;
	data->commands = NULL;
	data->last_pid = -2;
	data->infile = -2;
	data->outfile = -2;
	data->pipe_fd[0] = -2;
	data->pipe_fd[1] = -2;
	data->exit_status = 0;
	data->heredoc = NULL;
	data->stdin_old = -1;
	return (EXIT_SUCCESS);
}

static int	loop(t_data *data)
{
	while (1)
	{
		ignore_signals();
		data->user_line = readline(PROMPT);
		if (g_exit_status == 130)
		{
			data->exit_status = 130;
			g_exit_status = 0;
		}
		if (!data->user_line)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			free_and_exit_data(data, data->exit_status);
		}
		if (lexer(data) == EXIT_SUCCESS && parser(data) == EXIT_SUCCESS)
			g_exit_status = executer(data);
		else
			g_exit_status = 1;
		free_data(data);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv; 
	ft_bzero(&data, sizeof(t_data));
	 
	if (data.env == NULL)
		return (EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, &data.terminal);
	while (true)
	{
		data.free_value = 0;
		ft_readline(&data);
		copy_env_char(&data);
		if (!ft_tokenize(&data))
			continue ;
		parse_tokens(&data);
		if (data.parsing_error)
			ft_parsing_error(&data);
		ft_execution(&data);
		data.free_value = 1;
		ft_free_all(&data);
	}
	clear_history();
	return (data.exit_status);
}