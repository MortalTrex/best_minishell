/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/23 16:19:30 by mmiilpal         ###   ########.fr       */
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
void ft_free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->line);
		free(tmp);
	}
}

void ft_free_all(t_data *data)
{
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
	if (data->env)
	{
		ft_free_env(data->env);
		data->env = NULL;
	}
	printf("All should be free...\n");
}
