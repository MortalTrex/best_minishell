/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/25 17:55:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

sig_atomic_t	g_received_signal = 0;

// void ft_commands()
// {

// }


int	main(int argc, char **argv, char **envp)
{

	(void)envp;
	(void)argc;
	(void)argv;
	t_token *data;
	char *line;
	//t_data data;

	// READ COMMANDS
	while (true)
	{
		line = readline(PROMPT);

		data = ft_lexer(line);

		//execute(data);
		if (ft_strncmp(line, "exit", 4) == 0)

		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
	}
	return (0);
}


