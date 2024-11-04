#include "minishell.h"

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

void	ft_fds_dup2(t_data *data)
{
	dup2(data->fd[0], 0);
	dup2(data->fd[1], 1);
}

bool	is_builtin(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"))
		return (true);
	return (false);
}


// char		*get_env(t_data *data)
// {
// 	ssize_t i;
// 	size_t	len;

// 	if (!data->envc)
// 		return (NULL);
// 	len = ft_strlen(data->envc);
// 	if ((i = find_env(data)) != -1)
// 		return (ft_substr(data->envc[i], (len + 1), ft_strlen(data->envc[i])));
// 	return (NULL);
// }
