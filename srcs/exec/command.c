/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:52:35 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/04 16:57:12 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	exec_onecommand(t_ast_node *node, t_data *data, bool ispipe)
{
	int		status;

	if (!(node->argv))
		return (EXIT_SUCCESS);
	else if (is_builtin(node->argv[0]))
	{
		
		status = exec_builtin(node->argv, data);
	}
	else
		return (exec_child(node->argv, data));
}
