/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/24 16:16:04 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_data *data, char *msg)
{
	ft_free_all(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
void	ft_free_all(t_data *data)
{
	rl_clear_history();
	if (!data)
		return ;
	if (data->fd != NULL)
	{
		close(data->fd[0]);
		close(data->fd[1]);
	}
	if (data->tokens)
		ft_stackclear(&data->tokens);
	if (data->user_line)
	{
		free(data->user_line);
	}
	if (data->tok)
	{
		ft_stackclear(&data->tok);
	}
	if (data->ast)
		free_ast(data->ast);
	if (data->env)
		ft_envclear(&data->env);
}
