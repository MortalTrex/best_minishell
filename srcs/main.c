/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/29 13:33:20 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{

	(void)envp;
	(void)argc;
	(void)argv;
	t_token *tok;
	char *line;

	while (true)
	{
		line = readline("minishell> ");
		tok = ft_lexer(line);
		t_token *tokens = tok;
		while (tokens)
		{
			if (tokens->type == T_WORD)
				printf("T_WORD: %s\n", tokens->value);
			else if (tokens->type == T_OPERATOR)
				printf("T_OPERATOR: %s\n", tokens->value);
			else if (tokens->type == T_EOF)
				printf("T_EOF\n");
			tokens = tokens->next;
		}
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
		ft_stackclear(&tok);
	}
	return (0);
}
