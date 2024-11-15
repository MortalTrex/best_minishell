/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/15 20:30:40 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_path(char *cmd, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;
	char 	*path_to_find;

	i = 0;
	int len = 0;
	while (data->envc[len])
		len++;
	if (len <= 3)
		path_to_find = ft_strdup("_");
	else
		path_to_find = ft_strdup("PATH");
	while (data->envc[i] && ft_strnstr(data->envc[i], path_to_find, 4) == 0)
		i++;
	if (len <= 3)
	{
		char *path2 = ft_strdup("/usr/bin/");
		dir_path = ft_split(path2, ':');
	}
	else
		dir_path = ft_split(data->envc[i] + 5, ':');
	if (!dir_path)
		ft_close_fd(data, "Error: split failed\n");
	i = -1;
	while (dir_path[++i])
	{
		join_path = ft_strjoin(dir_path[i], "/");
		path = ft_strjoin(join_path, cmd);
		free(join_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	ft_free_tab(dir_path);
	return (NULL);
}

void	exec(t_data *data, char **cmd)
{
	char	*path;

	if (!cmd || !cmd[0])
		ft_close_fd(data, "Error: no command\n");
	if (!data->envc)
		ft_close_fd(data, "Error: no env\n");
	path = ft_path(cmd[0], data);
	if (!path)
	{
		ft_printf("Command '%s'", cmd[0]);
		ft_close_fd(data, " not found\n");
	}
	if (execve(path, cmd, data->envc) == -1)
		ft_close_fd(data, "execve fail\n");
}
