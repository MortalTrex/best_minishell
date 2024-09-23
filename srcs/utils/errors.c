/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/23 19:09:36 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *msg, int *fd)
{
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_msg_free_exit(char *msg, t_data *data)
{
	ft_stackclear(&data->tok);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_free_all(t_data *data)
{
	rl_clear_history();
	if (data->tokens)
		ft_stackclear(&data->tokens);
	if (data->user_line)
		free(data->user_line);
	if (data->tok)
		ft_stackclear(&data->tok);
	if (data->ast)
		free_ast(data->ast);
	if (data->env)
		ft_envclear(data->env);
}
