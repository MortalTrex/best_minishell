#include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	LESS_THAN,
	GREATER_THAN,
	DOUBLE_LESS_THAN,
	DOUBLE_GREATER_THAN
}					t_token_type;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;

