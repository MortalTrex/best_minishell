#include "minishell.h"

typedef enum e_token_type
{
	T_ATOM,
	T_PIPE,
	T_AND,
	T_OR,
	T_NEWLINE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APP,
	T_HEREDOC

}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

salut je suis "oui oui" suis