/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:22:20 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/19 14:30:43 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_wordchar(char c)

{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

int str_is_empty(char *str)
{
    if (!str)
        return (1);
    while (*str)
    {
        if (*str != ' ' && *str != '\t')
            return (0);
        str++;
    }
    return (1);
}

int check_quotes(char *str)
{
    bool sq;
    bool dq;
    
    sq = false;
    dq = false;
    while(*str)
    {
        if (*str == '\'' && !dq)
            sq = !sq;
        if (*str == '\"' && !sq)
            dq = !dq;
        str++;
    }
    return (sq || dq);
}