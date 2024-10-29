/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/29 16:13:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void parse_tokens(t_data *data)
{
	ft_expand_env_vars(&data->tok);
	printf("Tokens expanded...\n");
	data->ast = create_tree(&data->tok, data);
	printf("Tree created...\n");
	if (data->ast != NULL)
	{
		printf("AST constructed, printing...\n");
		print_ast(data->ast, 0);
		free_ast(&data->ast, data);
	}
}
