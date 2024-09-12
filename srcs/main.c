/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:17:40 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 16:11:54 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_global_state = 0;

// valgrind --leak-check=full ./minishell
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
// valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --log-file=log_errors.txt ./minishell

void	verify_builtin(char *line, t_data *data)
{
	if (ft_strncmp(line, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(line, "echo", 5) == 0)
		ft_echo(line);
	else if (ft_strncmp(line, "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(line, "export", 7) == 0)
		ft_export(data, line);
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
	t_token		*tok;
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;

	ast = 0;
	(void)envp;
	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	copy_env(envp, &data);
	while (true)
	{
		line = readline(PROMPT);
		tok = ft_lexer(line, &data);
		tokens = tok;
		print_tokens(tokens);
		ast = parse_tokens(tokens);
		//verify_builtin(line, &data);
		free(line);
		ft_stackclear(&tok);
		free_ast(ast);
	}
	return (0);
}
