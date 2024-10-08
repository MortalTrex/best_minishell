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
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	//printf("valeur split : %s\n", cmd_split[0]);
	if (!cmd_split || !cmd_split[0])
	{
		ft_free_tab(cmd_split);
		ft_error(data, "no cmd");
	}
	path = find_path(cmd, data);
	ft_printf("path %s\n", path);
	ft_printf("cmd %s\n", cmd);
	if (execve(path, cmd_split, data->envc) == -1)
	{
		ft_free_tab(cmd_split);
		ft_error(data, "execve fail");
	}
}