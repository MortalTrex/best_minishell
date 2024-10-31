/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/31 17:00:28 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_global_state = 0;

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

void	ft_readline(t_data *data)
{
	data->user_line = readline(PROMPT);
	signal(SIGINT, sigint_handler);
	if ((*data->user_line))
		add_history(data->user_line);
	if (data->user_line == NULL)
	{
		ft_printf("Exit\n");
		exit(0);
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
		ft_readline(&data);
		copy_env_char(&data);
		if (!ft_tokenize(&data))
			continue ;
		//print_tab(data.envc);
		ft_detect_builtin(&data);
		parse_tokens(&data);
		ft_execution(&data);
		data.free_value = 1;
		ft_free_all(&data);
	}
	data.free_value = 0;
	ft_free_all(&data);
	clear_history();
	return (0);
}
