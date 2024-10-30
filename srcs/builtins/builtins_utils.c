#include "minishell.h"

void	ft_swap_env_lines(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->line;
	a->line = b->line;
	b->line = temp;
}

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	bool	is_sort;

	is_sort = false;
	while (is_sort == false)
	{
		is_sort = true;
		tmp = env;
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->line, tmp->next->line) > 0)
			{
				ft_swap_env_lines(tmp, tmp->next);
				is_sort = false;
			}
			tmp = tmp->next;
		}
	}
}

void	copy_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		push_node_to_env(data, envp[i]);
		i++;
	}
	data->envc = malloc(sizeof(char *) * (i + 1));
	if (!data->envc)
		ft_error(data, "Malloc failed\n");
	i = 0;
	while (envp[i])
	{
		data->envc[i] = ft_strdup(envp[i]);
		if (!data->envc[i])
			ft_error(data, "Malloc failed\n");
		i++;
	}
	data->envc[i] = NULL;
}
