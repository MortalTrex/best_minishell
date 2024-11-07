/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/07 17:33:28 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	search_in_env(t_data *data, char *var)
{
	t_env	*tmp_env;
	char 	*name_var;
	int 	i;

	tmp_env = data->env;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name_var = ft_strndup(var, i);
	while (tmp_env)
	{
		if (!ft_strcmp(name_var, tmp_env->name))
		{
			free(tmp_env->line);
			free(tmp_env->name);
			free(tmp_env->value);
			tmp_env->line = NULL;
			tmp_env->name = NULL;
			tmp_env->value = NULL;
			free(name_var);
			return ;
		}
		tmp_env = tmp_env->next;
	}
	free(name_var);
}

void	ft_unset(char **argv, t_data *data)
{
	int i;

	i = 1;
	while (argv[i])
	{
		search_in_env(data, argv[i]);
		i++;
	}
}
