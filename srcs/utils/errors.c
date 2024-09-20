/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/20 17:10:39 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_perror_msg(char *msg, int *fd)
{
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

void ft_msg_free_exit(char *msg, t_data *data)
{
	ft_stackclear(&data->tok);
	perror(msg);
	exit(EXIT_FAILURE);
}

void ft_free_all(t_data *data)
{
	if (data->tokens)
	{
		ft_stackclear(&data->tokens);
		data->tokens = NULL;
	}
	if (data->user_line)
	{
		free(data->user_line);
		data->user_line = NULL;
	}
	if (data->tok)
	{
		ft_stackclear(&data->tok);
		data->tok = NULL;
	}
	if (data->ast)
	{
		free_ast(data->ast);
		data->ast = NULL;
	}
	printf("All should be free...\n");
}
