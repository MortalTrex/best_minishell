/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/20 18:00:10 by rbalazs          ###   ########.fr       */
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
// builtins_launch.c
bool		ft_detect_builtin(char **argv, t_data *data);

// builtins_utils.c
void		copy_env(char **envp, t_data *data);
void		copy_env_char(t_data *data);
void		ft_sort_env(t_env *env);
void		ft_swap_env_lines(t_env *a, t_env *b);

// env.c
char		*put_name(char *line);
char		*put_value(char *line);
t_env		*new_node_env(char *line, t_data *data);
void		push_node_to_env(t_data *data, char *line);
void		ft_env(char **argv, t_data *data);

// export.c
bool		check_double(t_data *data, char *line);
void		ft_exp_env(t_data *data);
void		change_value(t_data *data, char *old, char *new);
bool		check_change_value(t_data *data);
void		ft_export(char **argv, t_data *data);

// echo.c
void		ft_echo(char **argv, t_data *data);

// pwd.c
void		ft_pwd(t_data *data);

//	unset.c
void		search_in_env(t_data *data, char *var);
void		ft_unset(char **argv, t_data *data);

//	exit.c
bool		ft_is_number(char *str);
int			ft_value(int value);
void		ft_exit(char **argv, t_data *data);

//	cd.c
void		set_env_oldpwd(char *old_pwd, t_data *data);
void		set_env_pwd(char *new_pwd, t_data *data);
void		ft_move_directory(char *path, t_data *data);
void		set_home(t_data *data);
void		ft_cd(char **argv, t_data *data);

//////////////// EXECUTION ////////////////
// exec_cases.c
int			exec_pipe(t_ast_node *node, t_data *data);
int			exec_onecommand(char **cmd, t_data *data);
void    	multi_pipe(t_ast_node *node, t_data *data, int i);
void		one_pipe(t_ast_node *node, t_data *data);
void		no_pipe(t_ast_node *node, t_data *data);
void		read_pipe(t_ast_node *node, t_data *data, int i);
int  		exec_node(t_ast_node *node, t_data *data, bool ispipe);

// exec_core.c
char		*ft_path(char *cmd, t_data *data);
void		exec(t_data *data, char **cmd);

// exec_read.c
void		ft_execution(t_data *data);
void		count_levels(t_ast_node *node, int level, t_data *data);
void		read_ast(t_ast_node *node, t_data *data);

// exec_utils.c
bool		ft_is_delimiter(char *delimiter, char *str);
void		ft_fds_dup2(t_data *data);
bool		is_builtin(char *command);
void 	  	wait_commands(t_data *data);

// exec_heredoc.c
void		ft_process_heredoc(t_redir *redir, t_data *data);

// exec_redirs.c
void        read_heredoc(t_ast_node *node, t_data *data);
void        read_infile(t_ast_node *node, t_data *data);
void        read_outfile(t_ast_node *node, t_data *data);
void  		read_redirs(t_ast_node *node, t_data *data);

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
t_ast_node	*create_tree(t_token **current_token, t_data *data);
void		parse_tokens(t_data *data);

// create_node.c
t_ast_node	*ft_create_pipe_node(t_data *data, t_ast_node *left,
				t_ast_node *right);
t_redir		*ft_create_redir_node(t_token_type type, char *file);
t_ast_node	*ft_create_node(t_ast_node_type type);
void		ft_append_redir(t_redir **rds, t_redir *redir);

// get_clean_argv.c
char		**ft_ms_split(char const *str);

// expand_and_clean.c
char		**ft_expand_and_clean(char *str, t_data *data);

// expand_env_vars.c
char		*ft_get_env_value(char *var, t_data *data);
char		*ft_expand_env_vars(char *word, size_t *i, t_data *data);

// handle_quotes.c
char		*ft_get_str(char *str, size_t *i);
char		*ft_get_squote_string(char *str, size_t *i);
char		*ft_handle_dquotes(char *str, size_t *i, t_data *data);
char		*ft_clean_command(char *str, t_data *data);

// parse_s_command.c
bool		handle_redir(t_redir **redir, t_token **token, t_data *data);
bool		join_words(char **command, t_token **current, t_data *data);
t_ast_node	*simple_command(t_token **current_token, t_data *data);

// remove_quotes.c
char		*ft_clean_empty_strs(char *str);
char		*ft_remove_quotes(char *str);

// utils_parser.c
bool		is_redirection(t_token *token);
bool		check_pipe_syntax(t_token *tokens, t_data *data);
void		ft_parsing_error(t_data *data);
char		*ft_strjoin_free(char *s1, char *s2);

///////////SIGNALS//////////////

// signal.c
void		heredoc_sigint_handler(int sig);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
void		signals(t_data *data);

/////////////UTILS//////////////

// debug.c
void		print_ast(t_ast_node *node, int level);
void		print_tab(char **str);

// errors.c
void		ft_error(t_data *data, char *msg);
void		ft_close_fd(t_data *data, char *msg);
void		ft_error_quote(t_data *data);

// free.c
void		ft_free_command(t_ast_node *node);
void		free_node(t_ast_node *node);
void		free_ast(t_ast_node **node, t_data *data);
void		ft_free_all(t_data *data);

#endif
