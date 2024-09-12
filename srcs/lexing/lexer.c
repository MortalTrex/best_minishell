/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:48 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 16:26:21 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *line, t_data *data)
{
	if (!ft_tokenize(line, data))
		return (ft_stackclear(data), NULL);
	return (data->tokens);
}

