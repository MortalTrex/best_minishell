/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:48 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/12 17:36:34 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *line, t_data *data)
{
	t_token	*tokens;

	tokens = NULL;
	if (!ft_tokenize(line, &tokens, data))
		return (ft_stackclear(&tokens), NULL);
	return (tokens);
}

