/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:44 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/03 20:47:24 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <minishell.h>

typedef enum e_redir_type
{
	IN,
	OUT,
	D_APPEND,
	D_HEREDOC
}					t_redir_type;

typedef enum e_ast_node_type
{
	NODE_CMD,
	NODE_PIPE,
}					t_ast_node_type;

typedef struct s_redir
{
	char			*command;
	t_redir_type	type;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

// while (redir)
// checker type
// si un type est IN
// tu dois continuer la boucle pour verifier si c le seul
// si cest pas le cas tu dois prendre le dernier infile en param dans lexec
// here_doc char **arguments
// > ....
// > ....
// > ....
// > le mot delimitateur
// char **here_doc

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				*command;
	char				**argv;
	t_redir				*redir;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
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
	t_env			*env;
	char 			**envc;
	t_token			*tok;
	t_token			*tmp_token;
	char			*user_line;
	int				fd[2];
	t_ast_node		*ast;
	int				parsing_error;
	int				exit_status;
	int 			free_value;
	int 			nb_levels;
}					t_data;

#endif
