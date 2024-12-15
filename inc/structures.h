/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/14 19:23:54 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

# include <minishell.h>
# include <termios.h>

typedef enum e_token_type
{
	T_CMD,
	T_ARG,
	T_PIPE,
	T_ASSIGN,
	T_VARIABLE,
	T_VALUE_VAR,
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
	bool			to_expand;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_replace_variables
{
	size_t len;
	char *result;
	char *res_ptr;
	const char *start;
	const char *ptr;
	size_t var_len;
	char *var_name;
	char *var_value;
	size_t value_len;


}				t_replace_variables;

typedef struct s_fill_tokens
{
	t_token *last_token;
    t_token_type type;
    t_token *new_token;
    t_token_type subtype;
    t_token *extra_token;
    t_token *temp;
	char **words;

}				t_fill_tokens;


typedef struct s_match_tokens
{
	char				*new_prompt;
	char				*dest;
	bool				matched;
	size_t				token_len;
	int					i;
}				t_match_tokens;

typedef enum e_redir_type
{
	IN,
	OUT,
	D_APPEND,
	D_HEREDOC,
}					t_redir_type;


typedef struct s_redir
{
	char            *value;
	char			*file_here_doc;
	t_redir_type	type;
	int				hd_fd;
	int				in_fd;
	int 		   	out_fd;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;


typedef struct s_shell_list
{
	char				*command;
	char				**argv;
	pid_t				pid;
	t_redir				*redir;
	struct s_shell_list		*prev;
	struct s_shell_list		*next;
}					t_shell_list;

typedef enum e_ast_node_type
{
	NODE_CMD,
	NODE_PIPE,
}					t_ast_node_type;


typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_redir				*redir;
	char				*command;
	char				**argv;
	int					total_redirs;
	pid_t				pid;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*prev;
	struct s_ast_node	*next;
}					t_ast_node;


typedef struct s_env
{
	char			*line;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_token			*tok;
	t_env			*env;
	t_shell_list	*shell_list;
	t_ast_node      *new_ast;
	char			**envc;
	int				pipe_fd[2];
	char			*user_line;
	int				fd[2];
	int             stdin_backup;
	int             stdout_backup;
	t_ast_node		*ast;
	int				parsing_error;
	int				exit_status;
	int				last_pid;
	int				wstatus;
	int				free_value;
	int             nb_levels;
	struct termios	terminal;
	bool			isheredoc;
	bool            isoutfile;
	bool			isinfile;
}					t_data;

extern int			g_exit_status;

#endif