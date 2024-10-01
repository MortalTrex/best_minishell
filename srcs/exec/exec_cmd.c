#include <minishell.h>

char	*find_path(char *cmd, char **envp, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	dir_path = ft_split(envp[i] + 5, ':');
	if (!dir_path)
		ft_error(data, "Error: split failed");
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

void	exec_cmd(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(, 32);
	if (!cmd || !cmd[0])
		ft_error(data, "Error: empty command");
	path = find_path(cmd[0], data->env, data);
	if (!path || execve(path, cmd, data->env) == -1)
	{
		ft_free_tab(cmd);
		ft_error(data, "Error: command not found");
	}
}