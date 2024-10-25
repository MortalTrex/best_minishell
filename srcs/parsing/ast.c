/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/25 18:03:28 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void parse_tokens(t_data *data)
{
	printf("Parsing tokens...\n");
	// Vérifie l'emplacement des pipes pour savoir si tout est bon
	// if (!check_pipe_syntax(data->tmp_token))
	// 	return;
	// Expand les variables d'environnement, ce qui veut dire ?
	ft_expand_env_vars(&data->tok);
	// Crée l'arbre binaire
	data->ast = create_tree(data);
	if (data->ast != NULL)
	{
		printf("AST constructed, printing...\n");
		print_ast(data->ast, 0);
	}
}
