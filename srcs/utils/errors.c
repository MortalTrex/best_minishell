/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/18 19:08:24 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_data *data, char *msg)
{
	close(data->fd[0]);
	close(data->fd[1]);
	ft_error(data, msg);
}

void	ft_error(t_data *data, char *msg)
{
	ft_free_all(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	if (data->user_line)
		free(data->user_line);
	if (data->tok)
		ft_stackclear(&data->tok);
	if (data->env)
		ft_envclear(&data->env);
	if (data->envc)
		ft_free_tab(data->envc);
	// if (data->ast)
	// 	free_ast(data->ast);
}

void	ft_error_quote(t_data *data)
{
	ft_putstr_fd("minishell> unexpected EOF while looking for matching `", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
}
