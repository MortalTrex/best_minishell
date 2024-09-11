/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:50 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/11 10:00:57 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <minishell.h>

typedef enum e_token_type
{
	T_WORD,
	T_IO_NUMBER,
	T_NEWLINE,
	T_OPERATOR,
	T_EOF,
	T_BUILTIN,
	T_ENV_VAR
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

#endif
