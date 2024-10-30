/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:18:37 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/10/30 17:29:26 by mmiilpal         ###   ########.fr       */
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

}

