#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	T_WORD, // T_ATOM is a token that is not a special character (command, argument, file name)
	T_IO_NUMBER,
	T_NEWLINE,
	T_NAME,
	T_ERROR,
	T_EOF
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

#endif
