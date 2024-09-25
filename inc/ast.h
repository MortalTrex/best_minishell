/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:23:13 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/09/25 16:23:48 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef enum e_ast_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_SEQUENCE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

#endif
