/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/30 16:52:31 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////// INCLUDES ///////////////////////////

# include "../libft/libft.h"
# include "lexer.h"
# include "structures.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

////////////////////////// DEFINITIONS ////////////////////////////

# define PROMPT "minishell> "
# define ERR_SYN 1
# define ERR_MEM 2
# define BUFF_SIZE 4096

////////////////////////// FUNCTION PROTOTYPES /////////////////////////

///////////////// MAIN //////////////////

// main.c
void		print_tokens(t_data *data);
int			main(int argc, char **argv, char **envp);


// Errors
void		ft_error(t_data *data, char *msg);
bool		ft_is_wordchar(char c);
void		ft_close_fd(t_data *data, char *msg);
void		ft_error_quote(t_data *data);

// free.c
void		ft_free_command(t_ast_node *node);
void		free_node(t_ast_node *node);
void		free_ast(t_ast_node **node, t_data *data);
void		ft_free_all(t_data *data);


/////////////// BUILTIN //////////////////

// builtins_utils.c
void		copy_env(char **envp, t_data *data);
void		ft_sort_env(t_env *env);
void		ft_swap_env_lines(t_env *a, t_env *b);

// env.c
char		*put_name(char *line);
char		*put_value(char *line);
t_env		*new_node_env(char *line, t_data *data);
void		push_node_to_env(t_data *data, char *line);
void		ft_env(t_data *data);

// export.c
bool		check_double(t_data *data, char *line);
void        ft_exp_env(t_data *data);
void		change_value(t_data *data, char *old, char *new);
bool		check_change_value(t_data *data);
void		ft_export(t_data *data);

// echo.c
void		ft_echo(t_data *data);

// pwd.c
void		ft_pwd(void);

//	unset.c
void		search_in_env(t_data *data, char *var);
void		ft_unset(t_data *data);

//	exit.c
bool		ft_is_number(char *str);
int			ft_value(int value);
void		ft_exit(t_data *data);

//	cd.c
void        set_env_oldpwd(char *old_pwd, t_data *data);
void		set_env_pwd(char *new_pwd, t_data *data);
void		ft_move_directory(char *path, t_data *data);
void		set_home(t_data *data);
void		ft_cd(t_data *data);

//////////////// EXECUTION ////////////////
// exec_cases.c
int			exec_pipe(char *cmd1, char *cmd2, t_data *data);
int			exec_onecommand(char *cmd, t_data *data);

// exec_core.c
char 		*ft_path(char *cmd, t_data *data);
void 		exec(t_data *data, char *cmd);
void 		ft_process_infile(char *cmd, t_data *data, bool redir);
void 		ft_process_outfile(char *cmd, t_data *data);


// exec_read.c
void		ft_execution(t_data *data);

///////////// LEXING ///////////////

// append.c
bool		ft_append_operator(char **command, t_token **tokens);
bool		ft_append_word(char **command, t_token **tokens, t_data *data);

// tokenize.c
bool		ft_tokenize(t_data *data);
t_token		*get_tokens(char *command, t_data *data);

// grammar_check.c
bool		ft_is_operator(char c);
bool		ft_is_multi_char_operator(const char *str);
bool		ft_is_quote(char c);
bool		ft_skip_quotes(char *line, size_t *i);
bool		ft_is_separator(char *s);

// stack_utils.c
int			ft_strcmp(const char *s1, const char *s2);
t_token		*ft_stacknew(t_token_type type, char *value);
void		ft_stackadd_back(t_token **stack, t_token *new);
void		ft_stackclear(t_token **stack);
void		ft_envclear(t_env **env);

//////////////// PARSING //////////////////

// ast.c
void parse_tokens(t_data *data);
void print_ast(t_ast_node *node, int level);

// create_node.c
t_ast_node *ft_create_pipe_node(t_data *data, t_ast_node *left, t_ast_node *right);
t_redir *ft_create_redir_node(t_token_type type, char *file);
t_ast_node *ft_create_node(t_ast_node_type type);
void ft_append_redir(t_redir **rds, t_redir *redir);

// create_tree.c
t_ast_node *create_tree(t_token **current_token, t_data *data);

// parse_s_command.c
bool		handle_redir(t_redir **redir, t_token **token, t_data *data);
bool		join_words(char **command, t_token **current, t_data *data);
t_ast_node	*simple_command(t_token **current_token, t_data *data);

// utils_parser.c
bool	is_redirection(t_token *token);
bool check_pipe_syntax(t_token *tokens);
void ft_expand_env_vars(t_token **tokens);
void ft_parsing_error(t_data *data);

///////////SIGNALS//////////////

// signal.c
void	sigint_handler(int sig);

/////////////UTILS//////////////

// debug.c
void	print_ast(t_ast_node *node, int level);
void	print_tab(char **str);

// errors.c
void	ft_error(t_data *data, char *msg);
void	ft_close_fd(t_data *data, char *msg);
void	ft_error_quote(t_data *data);

// free.c
void	ft_free_command(t_ast_node *node);
void	free_node(t_ast_node *node);
void	free_ast(t_ast_node **node, t_data *data);
void	ft_free_all(t_data *data);

#endif
