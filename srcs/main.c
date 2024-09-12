/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 18:00:39 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_global_state = 0;

// valgrind --leak-check=full ./minishell
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --log-file=log_errors.txt ./minishell

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
		else if (tokens->type == T_ENV_VAR)
			printf("\033[1;33mT_ENV_VAR: %s\033[0m\n", tokens->value);
		else if (tokens->type == T_BUILTIN)
			printf("\033[1;35mT_BUILTIN: %s\033[0m\n", tokens->value);
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;
	t_ast_node	*ast;

	ast = 0;
	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	copy_env(envp, &data);
	while (true)
	{
		line = readline(PROMPT);
		if (!ft_tokenize(line, &data.tok, &data))
			return (ft_stackclear(&data.tok), 0);
		data.tokens = data.tok;
		print_tokens(data.tokens);
		//ast = parse_tokens(tokens);
		free(line);
		ft_stackclear(&data.tok);
		free_ast(ast);
	}
	return (0);
}
