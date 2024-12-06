/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 19:59:12 by dagudelo         ###   ########.fr       */
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
}

void 	ft_error_exit(t_data *data, char *msg)
{
	ft_error(data, msg);
	exit(1);
}

void	ft_error_quote(t_data *data)
{
	ft_putstr_fd("minishell> unexpected EOF while looking for matching ` or \"",
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
}
