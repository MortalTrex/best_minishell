/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 22:37:09 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/13 10:59:53 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_levels(t_ast_node *node, int level, t_data *data)
{
	if (!node)
		return ;
	data->nb_levels = level;
	if (node->right)
		ft_count_levels(node->right, level + 1, data);
}

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (true);
	return (false);
}

void	close_hd(t_redir *redir, t_data *data)
{
	if (redir && redir->hd_fd != -1)
		close(redir->hd_fd);
	close(STDIN_FILENO);
	if (data && data->fd[0] != -1)
		close(data->fd[0]);
}
