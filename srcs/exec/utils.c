#include "minishell.h"

char		*get_env(t_data *data
{
	ssize_t i;
	size_t	len;

	if (!data->envc)
		return (NULL);
	len = ft_strlen(data->envc);
	if ((i = find_env(data)) != -1)
		return (ft_substr(data->envc[i], (len + 1), ft_strlen(data->envc[i])));
	return (NULL);
}