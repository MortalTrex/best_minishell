/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/03 18:11:13 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_global_state = 0;

//valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

int main(int argc, char **argv, char **envp)
{
	t_data data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	//copy_env(envp, &data);
	copy_env_char(envp, &data);
	while (true)
	{
		data.user_line = readline(PROMPT);
		if (data.user_line != NULL)
			add_history(data.user_line);
		//signals();
		if (!ft_tokenize(&data))
			return (ft_free_all(&data), 0);
		ast_print_tokens(data.tok);
		parse_tokens(&data);
		ft_free_all(&data);
	}
	clear_history();
	return (0);
}
