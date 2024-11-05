/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/05 16:51:25 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status;

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

static void	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	copy_env(envp, data);
	data->exit_status = 0;
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	data->heredoc = false;
	tcgetattr(STDIN_FILENO, &data->terminal);
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
		ft_execution(&data);
		data.free_value = 1;
		ft_free_all(&data);
	}
	data.free_value = 0;
	ft_free_all(&data);
	return (data.exit_status);
}
