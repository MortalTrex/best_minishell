/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:13:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *cmd, char *error,
				int exit_status, t_data *data)
{
	print_error(cmd, error, NULL);
	data->exit_status = exit_status;
	ft_free_all_and_exit(data, data->exit_status);
}

static char	*check_if_directory(char *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		perror(cmd);
		data->exit_status = 127;
		ft_free_all_and_exit(data, data->exit_status);
	}
	if (S_ISDIR(path_stat.st_mode))
		handle_error(cmd, "Is a directory", 126, data);
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	if (access(cmd, F_OK) == -1)
		handle_error(cmd, "No such file or directory", 127, data);
	else
		data->exit_status = 126;
	return (cmd);
}

static char	*locate_command_in_paths(char **path_dirs, char *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	if (cmd[0] == '\0')
		return (ft_free_tab(path_dirs), NULL);
	i = 0;
	while (path_dirs[i])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (cmd_path && access(cmd_path, X_OK) == 0)
			return (ft_free_tab(path_dirs), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_free_tab(path_dirs);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_data *data)
{
	char	**path_dirs;
	char	*path_var;

	if (ft_strchr(cmd, '/'))
		return (check_if_directory(cmd, data));
	path_var = ft_getenv(data->env, "PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	free(path_var);
	if (!path_dirs)
		return (NULL);
	return (locate_command_in_paths(path_dirs, cmd));
}
