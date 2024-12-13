/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:23 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/12 10:10:32 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
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

	tmp_env = data->env;
	printf("var: %s\n", var);
	while (tmp_env)
	{
		if (!ft_strcmp(var, tmp_env->name))
		{
			printf("found\n");
			free(tmp_env->line);
			tmp_env->line = NULL;
			free(tmp_env->name);
			tmp_env->name = NULL;
			free(tmp_env->value);
			tmp_env->value = NULL;
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	ft_unset(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		search_in_env(data, argv[i]);
		i++;
	}
	data->exit_status = 0;
}
