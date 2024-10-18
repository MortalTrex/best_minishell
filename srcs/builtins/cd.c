/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/18 17:13:40 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	set_env(char *new_pwd)
// {
	
// }

void 	ft_move_directory(char *path)
{
	char *new_pwd;

	if (chdir(path) == 0)
		ft_printf("Path not found\n");
	new_pwd = getcwd(NULL, 0);
	//set_env(new_pwd);
	printf("%s\n", new_pwd);
	free(new_pwd);
}

void	ft_cd(t_data *data)
{
	t_token	*current;

	current = data->tok;
	if (current->next)
	{
	 	current = current->next;
		ft_move_directory(current->value);
	}
	//printf("current->value: %s\n", current->value);
}
