/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:18:37 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/30 19:27:14 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expand_and_clean(char *str, t_data *data)
{
	char	**clean;
	size_t	i;

	str = ft_clean_command(str, data);
	if (!str)
		return (NULL);
	str = ft_clean_empty_strs(str);
	if (!str)
		return (NULL);
	clean = ft_ms_split(str);
	if (!clean)
		return (NULL);
	i = 0;
	while (clean[i])
	{
		clean[i] = ft_remove_quotes(clean[i]);
		i++;
	}
	return (clean);
}

