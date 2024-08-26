/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/26 15:07:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* bool is_whiteSpace(char c)
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
	tokens = ft_token_split(line);
	int i = 0;

	while (tokens[i])
	{
		ft_printf("token num [%i] is: %s\n", i, tokens[i]);
		i++;
	}

} */

int	main(int argc, char **argv, char **envp)
{

	(void)envp;
	(void)argc;
	(void)argv;
	t_token *tokens;
	char *line;

	while (true)
	{
		line = readline("minishell> ");
		tokens = ft_lexer(line);
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
	}
	return (0);
}
