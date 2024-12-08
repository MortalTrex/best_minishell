/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 21:21:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// valgrind --suppressions=rlsupp.txt --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
int		g_exit_status;

void	ft_readline(t_data *data)
{
	data->user_line = readline(PROMPT);
	signal(SIGINT, sigint_handler);
	if (data->user_line)
		add_history(data->user_line);
	if (data->user_line == NULL)
	{
		ft_printf("Exit\n");
		// ft_free_all(mdata);
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
	tcgetattr(STDIN_FILENO, &data.terminal);
	while (true)
	{
		data.free_value = 0;
		ft_readline(&data);
		copy_env_char(&data);
		if (!ft_found_token_in_argv(&data))
			continue ;
		
		ft_parsing_tokens(&data);
		ft_execution(&data);
		data.free_value = 1;
		ft_free_all(&data);
		// data.exit_status = 0;
	}
	clear_history();
	return (data.exit_status);
}