/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/28 15:04:53 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void parse_tokens(t_data *data)
{
	// Vérifie l'emplacement des pipes pour savoir si tout est bon
	// if (!check_pipe_syntax(data->tmp_token))
	// 	return;
	ft_expand_env_vars(&data->tok);
	printf("Tokens expanded...\n");
	data->ast = create_tree(data);
	printf("Tree created...\n");
	if (data->ast != NULL)
	{
		printf("AST constructed, printing...\n");
		print_ast(data->ast, 0);
		free_ast(data->ast);
	}

}
