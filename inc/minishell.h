/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/25 16:03:19 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////// INCLUDES ///////////////////////////

# include "../libft/libft.h"
# include "ast.h"
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

////////////////////////// FUNCTION PROTOTYPES /////////////////////////

// MAIN

// main.c
void		print_tokens(t_data *data);
int			main(int argc, char **argv, char **envp);

// Pipex
char		*find_path(char *cmd, char **envp, t_data *data);
void		exec(char *arg, char **envp, t_data *data);
void		ft_process_infile(char **argv, char **envp, t_data *data);
void		ft_process_outfile(char **argv, t_data *data, char **envp, int argc);

// Errors
void		ft_error(t_data *data, char *msg);
bool		ft_is_wordchar(char c);
void		ft_free_all(t_data *data);

// BUILTINS

// env.c
void		copy_env(char **envp, t_data *data);
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

// LEXING

// append.c
void		ft_append_operator(t_data *data, char *line, unsigned int *i);
bool		ft_append_word(t_data *data, char *token_buffer);
bool		ft_append_word_quotes(char *token_buffer, int *buffer_index,
				char *line, unsigned int *i);
void		ft_append_env_var(t_data *data, char *line, unsigned int *i);

// tokenize.c
bool		ft_finalize_tokenization(t_data *data, char *token_buffer, int buffer_index, bool is_quotes);
bool		ft_process_operator(t_data *data, unsigned int *i, char *token_buffer, int *buffer_index);
bool		ft_process_whitespace(t_data *data, unsigned int *i, char *token_buffer, int *buffer_index);
bool		ft_tokenize(t_data *data);

// grammar_check.c
bool		ft_is_operator(char c);
bool		ft_is_multi_char_operator(const char *str);
bool		ft_is_quote(char c);
bool		ft_skip_quotes(char *line, unsigned int *i);

// stack_utils.c
int			ft_strcmp(const char *s1, const char *s2);
t_token		*ft_stacknew(int type, char *value);
void		ft_stackadd_back(t_token **stack, t_token *new);
void		ft_stackclear(t_token **stack);
void		ft_envclear(t_env **env);

// PARSING

// ast.c
t_ast_node	*create_ast_node(t_ast_node_type type, char *value);
void		free_ast(t_ast_node *root);
void		print_ast(t_ast_node *root, int depth);
void		ft_expand_env_vars(t_token **tokens);
void		parse_tokens(t_data *data);
t_ast_node	*parse_command(t_token **tokens);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_sequence(t_token **tokens);

#endif
