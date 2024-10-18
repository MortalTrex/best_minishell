/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:12 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/18 20:25:17 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinchar(char const *s1, char c)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(s1) + 1;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (res);
}
char	*put_name(char *line)
{
	int i;
	char *res;

	i = 0;
	while (line && line[i] != ' ')
	{
		res = joinchar(res, line[i]);
		i++;
	}
	return(res);
}

t_env	*new_node_env(char *line, t_data *data)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->line = ft_strdup(line);
	new_node->name = ft_strdup(line);
	printf("%s\n", new_node->name);
	if (!new_node->line)
	{
		free(new_node);
		ft_error(data, "Malloc failed\n");
	}
	new_node->next = NULL;
	return (new_node);
}

void	push_node_to_env(t_data *data, char *env_line)
{
	t_env	*new_node;
	t_env	*current;

	new_node = new_node_env(env_line, data);
	if (!new_node)
		return ;
	current = data->env;
	if (data->env == NULL)
		data->env = new_node;
	else
	{
		current = data->env;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
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
}

void	copy_env_char(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
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

// debug function
void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->envc[i])
	{
		printf("%s\n", data->envc[i]);
		i++;
	}
}

void	ft_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		ft_printf("%s\n", current->line);
		current = current->next;
	}
}