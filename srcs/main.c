/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/29 18:48:07 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_global_state = 0;

// valgrind --leak-check=full ./minishell

void	verify_builtin(char *line, char **envp)
{
	if (ft_strncmp(line, "pwd", 4) == 0)
		ft_pwd(envp);
	else if (ft_strncmp(line, "echo", 5) == 0)
		ft_echo(line);
	else if (ft_strncmp(line, "env", 4) == 0)
		ft_env(envp);
	else if (ft_strncmp(line, "exit", 5) == 0)
		exit(0);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == T_WORD)
			printf("\033[1;32mT_WORD: %s\033[0m\n", tokens->value);
		else if (tokens->type == T_OPERATOR)
			printf("\033[1;34mT_OPERATOR: %s\033[0m\n", tokens->value);
		else if (tokens->type == T_EOF)
			printf("\033[1;31mT_EOF\033[0m\n");
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok;
	char	*line;
	t_token	*tokens;

	(void)envp;
	(void)argc;
	(void)argv;
	// ft_bzero(&tok, sizeof(t_token));
	while (true)
	{
		line = readline(PROMPT);
		tok = ft_lexer(line);
		tokens = tok;
		print_tokens(tokens);
		verify_builtin(line, envp);
		free(line);
		ft_stackclear(&tok);
	}
	//ft_free_all(tok);
	return (0);
}
