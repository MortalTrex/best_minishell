#include <minishell.h>

char	*find_path(char *cmd, t_data *data)
{
	char	*path;
	int		i;
	char	**dir_path;
	char	*join_path;

	i = 0;
	while (data->envc[i] && ft_strnstr(data->envc[i], "PATH", 4) == 0)
		i++;
	dir_path = ft_split(data->envc[i] + 5, ':');
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

void	exec_cmd(t_data *data, char *cmd)
{
	char	*path;

	if (!cmd || !cmd[0])
		ft_error(data, "Error: empty command");
	path = find_path(cmd, data);
	if (!path || execve(path, &cmd, data->envc) == -1)
		ft_error(data, "Error: command not found");
}