/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:18 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/09 17:01:33 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_export(t_data *data, char *line)
{
	char	*value;
	int		i;

	i = 6;
	while (line[i] == ' ')
		i++;
	value = ft_strdup(line + i);
	printf("export vaut : %s\n", value);
	push_node_to_env(data, value);
}
