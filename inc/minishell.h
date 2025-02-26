/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 14:52:40 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR 1
# define SUCCESS 0

////////////////////////// INCLUDES ///////////////////////////

# include "../libft/libft.h"
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
# define FD_IMPAIR_0 10
# define FD_IMPAIR_MIDDLE 11
# define FD_IMPAIR_END 12
# define FD_PAIR_MIDDLE 13
# define FD_PAIR_END 14
# define S_QUOTE '\''
# define D_QUOTE '\"'

////////////////////////// FUNCTION PROTOTYPES /////////////////////////

////////////////////////// LEXING ////////////////////////////

//	expand.c
int						get_quote(char *str, char c);
char					*expander(char *str, t_data *shell);

//	grammar_check.c
int						str_is_empty_or_space_only(char *str);
int						valid_quotes(char *str);
void					set_delimiter_quote_status(t_token *token);
int						len_between_tokens(char *str, int i, char c);
int						len_invalid_type(char *str);

// heredoc.c
void					unlink_heredoc(t_data *shell);
int						handle_heredoc(t_token *tmp, t_data *shell,
	int option);

//	lex.c
int						lexer(t_data *shell);

//	redir_types.c
int						get_type(char *str);
void					assign_type_redirections(t_token *tokens);

//	remove_quotes.c
void					remove_quotes(t_token *tokens);

//	string_utils.c
char					*get_value_after_expansion(char *str, t_data *shell,
							int *i);

//	syntax_check.c
int						case_heredoc_syntax(t_token *tokens, t_data *shell);
int						check_syntax(t_token *tokens, t_data *shell);

////////////////////////// PARSING ////////////////////////////

// create_command.c
t_command				*get_command(t_token *tokens);
void					add_command_back(t_command **commands,
	t_command *new_node);

//	parse.c
char					**get_cmd_array_from_tokens(t_token *tokens);
bool					is_builtin(char *cmd);
int						parser(t_data *shell);

//	redirs_utils.c
void					handle_redirections(t_token *tokens,
							t_command *command);

//	tokens_utils.c
t_token					*get_next_pipe(t_token *token);
int						count_not_null_tokens(t_token *tokens);

////////////////////////// BUILTINS ////////////////////////////

//	cd.c
int						ft_cd(t_command *commands, t_data *shell);

//	echo.c
int						ft_echo(t_command *commands);

//	env_init.c
t_env					*init_default_env(void);
t_env					*init_env(char **env);
char					**init_env_array(t_env *env_head);

//	env_set_free.c
void					free_env(t_env *env);
char					*ft_getenv(t_env *env_list, char *key);
void					ft_setenv(t_env *env_head, char *name, char *value);

//	env_utils.c
char					*get_env_value(char *str, char *var_name);
t_env					*init_env_node(char *str);
t_env					*init_default_env_node(char *var_name, char *value);
void					add_back_env_var(t_env **head, t_env *new_node);

//	env.c
int						ft_env(t_data *shell);

//	exit.c
void					ft_exit(t_command *commands, t_data *shell, bool pipe);

//	export_utils.c
int						free_and_return(char *curr_dir, char *old_dir, int ret);
int						handle_chdir_error(char *curr_dir, char *old_dir);

//	export.c
int						ft_export(char **cmd, t_data *shell);

//	pwd.c
int						ft_pwd(t_command *commands);

//	unset.c
int						var_exists(t_env *env_head, char *var_name);
int						ft_unset(char **cmd, t_data *shell);

////////////////////////// EXEC ////////////////////////////

//	exec_cmd.c
void					handle_error(char *cmd, char *error, int exit_status,
							t_data *shell);
char					*get_cmd_path(char *cmd, t_data *shell);

//	exec_fds_utils.c
void					duplicate_fd(int fd, int new_fd, t_data *shell,
							int exit_status);
void					close_fds(t_data *shell);
void					close_pipe_fds(t_data *shell);

//	exec_open.c
void					get_fd_in(t_token *redirections, t_data *shell);
void					get_fd_out(t_token *redirections, t_data *shell);

//	exec_redirs.c
void					get_fds(t_token *redirections, t_data *shell);
void					open_and_redirect_fd(t_command *current,
							t_data *shell);
void					has_no_filename(t_command *current, t_data *shell,
							int prev_fd);

//	exec.c
int						executer(t_data *shell);

// utils.c
void					write_line_to_heredoc(int fd, char *tmp, t_data *shell,
							int quotes_status);
void					pipe_and_fork(t_command *current, t_data *shell);
void					wait_commands(t_data *shell);

////////////////////////// UTILS ////////////////////////////

//	errors.c
int						syntax_error_eof(void);
int						syntax_error_in_token(char *token, t_data *shell);
void					write_error(char *cmd, char *error, char *arg);
void					write_warning(char *arg);
int						invalid_arg(int argc);

//	free.c
void					free_and_exit_shell(t_data *shell, int exit_code);
void					free_shell(t_data *shell);
void					free_tokens(t_token **tokens);
void					free_commands(t_command **commands);

// stack_utils.c
t_token					*create_token(char *value, int type, int quotes_status);
void					add_token_back(t_token **tokens, t_token *new_node);
char					**init_array(int size);
void					free_array(char **arr);

////////////////////////// SIGNALS ////////////////////////////

//	signals.c
void					catch_sigint(int signum);
void					heredoc_sigint(int signum);
void					ignore_signals(void);

#endif
