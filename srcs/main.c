/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/25 17:47:01 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool is_whiteSpace(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (true);
    return (false);
}

bool is_split_token(char c)
{
    if (is_whiteSpace(c) || c == '|')
        return (true);
    return (false);
}

void token_function(char *line)
{
	char **tokens;
	tokens = ft_split(line, ' ');
	int i = 0;

	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
	
}

int	main(int argc, char **argv, char **envp)
{

	(void)envp;
	(void)argc;
	(void)argv;

	char *line;

	while (true)
	{
		line = readline("minishell> ");

		token_function(line);

		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
	}
	return (0);
}
