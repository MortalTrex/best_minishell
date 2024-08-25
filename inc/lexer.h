#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	T_ATOM, // T_ATOM is a token that is not a special character (command, argument, file name)
	T_PIPE,
	T_AND,
	T_OR,
	T_VAR, // T_VAR is a token that is a variable
	T_NEWLINE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APP,
	T_HEREDOC,
	T_ERROR
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

#endif
