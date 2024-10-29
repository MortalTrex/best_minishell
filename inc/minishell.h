/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/29 17:02:17 by mmiilpal         ###   ########.fr       */
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
# define ERR_SYN "syntax error near unexpected token"
# define ERR_MEM "memory allocation error"
# define BUFF_SIZE 4096

////////////////////////// FUNCTION PROTOTYPES /////////////////////////

// MAIN

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

// BUILTINS

// env.c
void		copy_env(char **envp, t_data *data);
void  		copy_env_char(char **envp, t_data *data);
void		ft_env(t_data *data);
void		push_node_to_env(t_data *data, char *line);
void		ft_print_env(t_data *data);
t_env		*new_node_env(char *line, t_data *data);

// export.c
void		ft_export(t_data *data);

// echo.c
void		ft_echo(char *line);
void		print_line(char *line, int start, int len);

// pwd.c
void		ft_pwd(void);

//	unset.c
void		ft_unset(t_data *data);

//	exit.c
void		ft_exit(t_data *data);

//	cd.c
void	ft_cd(t_data *data);

// LEXING

// append.c
bool	ft_append_operator(char **command, t_token **tokens);
bool	ft_append_word(char **command, t_token **tokens, t_data *data);

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

// PARSING

// ast.c
void parse_tokens(t_data *data);
void print_ast(t_ast_node *node, int level);

// create_node.c
t_ast_node *ft_create_pipe_node(t_ast_node *left, t_ast_node *right);
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

// SIGNALS

bool	signals(t_data *data);

void	print_tab(char **str);

#endif
