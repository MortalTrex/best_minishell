/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:36:48 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/29 12:36:49 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *line)
{
	t_token	*tokens;

	tokens = NULL;
	if (!ft_tokenize(line, &tokens))
		return (ft_stackclear(&tokens), NULL);
	return (tokens);
}
