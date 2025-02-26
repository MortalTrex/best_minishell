/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:31:55 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/26 15:31:42 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *cmd, char *error,
				int exit_status, t_data *shell)
{
	write_error(cmd, error, NULL);
	shell->exit_status = exit_status;
	free_and_exit(shell, shell->exit_status);
}

static char	*check_if_directory(char *cmd, t_data *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		perror(cmd);
		shell->exit_status = 127;
		free_and_exit(shell, shell->exit_status);
	}
	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		handle_error(cmd, "Is a directory", 126, shell);
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!S_ISDIR(path_stat.st_mode))
	{
		if (access(cmd, F_OK) == -1)
			handle_error(cmd, "No such file or directory", 127, shell);
		else
			shell->exit_status = 126;
		return (cmd);
	}
	return (NULL);
}

static char	*locate_command_in_paths(char **path_dirs, char *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	if (cmd[0] == '\0')
	{
		free_array(path_dirs);
		return (NULL);
	}
	while (path_dirs[i++])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (cmd_path && access(cmd_path, X_OK) == 0)
		{
			free(temp);
			free_array(path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		free(temp);
	}
	free_array(path_dirs);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_data *shell)
{
	char	**path_dirs;
	char	*path_var;

	if (ft_strchr(cmd, '/') != NULL)
		return (check_if_directory(cmd, shell));
	path_var = ft_getenv(shell->env_list, "PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (free(path_var), NULL);
	free(path_var);
	return (locate_command_in_paths(path_dirs, cmd));
}
