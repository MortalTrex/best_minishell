/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:33 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/21 14:57:51 by rbalazs          ###   ########.fr       */
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
	free(path_to_find);
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
			return (ft_free_tab(dir_path), path);
		free(path);
	}
	ft_free_tab(dir_path);
	return (NULL);
}

void	exec(t_data *data, char **cmd)
{
	char	*path;
	char	*pwd_path;
	char    *cmd_minishell;

	pwd_path = getcwd(NULL, 0);
	cmd_minishell = ft_strjoin(pwd_path, "/minishell");
	if (!cmd || !cmd[0])
		ft_close_fd(data, "Error: no command\n");
	if (!data->envc)
		ft_close_fd(data, "Error: no env\n");
	if (ft_strncmp(cmd[0], "./minishell", 11) == 0)
	{
		if (execve(cmd_minishell, cmd, data->envc) == -1)
			ft_close_fd(data, "execve fail\n");
	}
	path = ft_path(cmd[0], data);
	if (!path)
	{
		ft_printf("Command '%s'", cmd[0]);
		ft_close_fd(data, " not found\n");
	}
	if (execve(path, cmd, data->envc) == -1)
		ft_close_fd(data, "execve fail\n");
}
