/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:50 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/28 00:56:42 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// typedef enum e_token_type
// {
// 	T_CMD,
// 	T_ARG,
// 	T_OPERATOR,
// 	T_PIPE,
// 	T_REDIR_IN,
// 	T_INFILE,
// 	T_REDIR_OUT,
// 	T_OUTFILE,
// 	T_REDIR_APPEND,
// 	T_APPENDFILE,
// 	T_REDIR_HERE,
// 	T_BUILTIN,
// 	T_WORD,
// }					t_token_type;

typedef enum e_token_type
{
	T_CMD,
	T_ARG,
	T_PIPE,
	T_ASSIGN,
	T_VARIABLE,	
	T_REDIR_IN,
	T_INFILE,
	T_REDIR_OUT,
	T_OUTFILE,
	T_REDIR_APPEND,
	T_APPENDFILE,
	T_REDIR_HERE,
	T_DELIMITER,
	T_WORD,
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

#endif
