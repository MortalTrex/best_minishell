/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:18 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/13 10:59:15 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_commands(t_ast_node *node, t_data *data)
{
	t_ast_node	*current;
	int				i;

	i = 0;
	current = node;
	while (current)
	{
		ft_multi_pipe(current, data, i);
		current = current->right;
		i++;
	}
}

void	ft_execution(t_data *data)
{
	if (!data->ast || !data)
		return ;
	ft_count_levels(data->ast, 0, data);
	if (data->nb_levels == 0)
	{
		ft_read_heredoc(data->ast, data);
		ft_no_pipe(data->ast, data);
	}
	else if (data->nb_levels >= 1)
		ft_read_commands(data->ast, data);
	ft_erase_all_temp_here_doc(data->ast);
}
