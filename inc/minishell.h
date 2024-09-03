/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:47 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/03 17:19:47 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

////////////////////////// INCLUDES ///////////////////////////

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "lexer.h"
# include "structures.h"
# include "ast.h"

////////////////////////// DEFINITIONS ////////////////////////////

# define PROMPT "minishell> "

////////////////////////// FUNCTION PROTOTYPES /////////////////////////

// Pipex
char	*find_path(char *cmd, char **envp);
void	exec(char *arg, char **envp);
void	ft_process_infile(char **argv, int *fd, char **envp);
void	ft_process_outfile(char **argv, int *fd, char **envp, int argc);

// Errors
void	ft_perror_msg(char *msg, int *fd);
void	ft_msg_free_exit(char *msg, t_token **tokens);
bool	ft_is_wordchar(char c);

// Builtins
void	ft_echo(char *line);
void	print_line(char *line, int start, int len);
void	ft_env(char **envp);
void	ft_pwd(char **envp);

/* lexer */

// lexer.c
t_token	*ft_lexer(char *line);

// append.c
void	ft_append_operator(t_token **tokens, char *line, unsigned int *i);
bool	ft_append_word(t_token **tokens, char *line, unsigned int *i);
void	ft_append_word_quotes(t_token **tokens, char *line, unsigned int *i);

// tokenize.c
bool	ft_tokenize(char *line, t_token **tokens);

// grammar_check.c
bool	ft_is_operator(char c);
bool	ft_is_quote(char c);
bool	ft_skip_quotes(char *line, unsigned int *i);

// stack_utils.c
t_token	*ft_stacknew(int type, void *value);
void	ft_stackadd_back(t_token **stack, t_token *new);
t_token	*ft_stacklast(t_token *stack);
void	ft_stackclear(t_token **stack);
t_token	*ft_stacknew_char(int type, char value);

// ast.c
t_ast_node *create_ast_node(t_ast_node_type type, char *value);
void free_ast(t_ast_node *root);
void print_ast(t_ast_node *root, int depth);
t_ast_node	*parse_tokens(t_token *tokens);

#endif
