/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/02 23:39:31 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

static void	init_minishell(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	data->exit_status = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
	copy_env(envp, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_minishell(&data, envp);
	while (true)
	{
		signals();
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
		print_tokens(&data);
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
	clear_history();
	return (0);
}
