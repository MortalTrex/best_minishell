/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/02 18:50:27 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_global_state = 0;

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

void	print_tokens(t_data *data)
{
	t_token	*tmp = data->tok;

	while (tmp)
	{
		if (tmp->type == T_WORD)
			printf("\033[1;32mT_WORD: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_OPERATOR)
			printf("\033[1;34mT_OPERATOR: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_BUILTIN)
			printf("\033[1;35mT_BUILTIN: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_APPEND)
			printf("\033[1;37mT_REDIR_APPEND: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_HERE)
			printf("\033[1;38mT_REDIR_HERE: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_IN)
			printf("\033[1;34mT_REDIR_IN: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_REDIR_OUT)
			printf("\033[1;30mT_REDIR_OUT: %s\033[0m\n", tmp->value);
		else if (tmp->type == T_PIPE)
			printf("\033[1;36mT_PIPE: %s\033[0m\n", tmp->value);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	copy_env(envp, &data);
	while (true)
	{
		data.free_value = 0;
		data.user_line = readline(PROMPT);
		signal(SIGINT, sigint_handler);
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
		//ft_execution(&data);
		data.free_value = 1;
		ft_free_all(&data);
	}
	data.free_value = 0;
	ft_free_all(&data);
	clear_history();
	return (0);
}
