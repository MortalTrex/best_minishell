/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/31 18:11:02 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_oldpwd(char *old_pwd, t_data *data)
{
	t_env	*current;
	char	*new_line;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->name, "OLDPWD", 6) == 0)
		{
			free(current->line);
			free(current->value);
			free(current->name);
			new_line = ft_strjoin("OLDPWD=", old_pwd);
			current->line = new_line;
			current->value = ft_strdup(old_pwd);
		}
		current = current->next;
	}
}

void	set_env_pwd(char *new_pwd, t_data *data)
{
	t_env	*current;
	char	*new_line;
	char	*old_pwd;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->name, "PWD", 3) == 0)
		{
			old_pwd = ft_strdup(current->value);
			free(current->line);
			free(current->value);
			free(current->name);
			new_line = ft_strjoin("PWD=", new_pwd);
			current->line = new_line;
			current->value = ft_strdup(new_pwd);
		}
		current = current->next;
	}
	if (old_pwd)
	{
		set_env_oldpwd(old_pwd, data);
		free(old_pwd);
	}
}

void	ft_move_directory(char *path, t_data *data)
{
	char	*new_pwd;

	if (chdir(path) == 0)
		ft_printf("Path not found\n");
	new_pwd = getcwd(NULL, 0);
	set_env_pwd(new_pwd, data);
	printf("%s\n", new_pwd);
	free(new_pwd);
}

void	set_home(t_data *data)
{
	t_env	*current;

	current = data->env;
	printf("set_home\n");
	while (current)
	{
		if (ft_strncmp(current->name, "HOME", 4) == 0)
			ft_move_directory(current->value, data);
		current = current->next;
	}
}

// void	ft_cd(char **argv, t_data *data)
// {
// 	t_token	*current;

// 	current = data->tok;
// 	if (current->next)
// 	{
// 		current = current->next;
// 		ft_move_directory(current->value, data);
// 	}
// 	else if (current->next == NULL)
// 		set_home(data);
// }
