/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:13:32 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/28 18:57:51 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define SQ '\''
# define DQ '\"'

////////////////////////// FUNCTION PROTOTYPES /////////////////////

////////////////////////// LEXING /////////////////////////////////

//	expand.c
int						get_quote(char *str, char c);
char					*expanding(char *str, t_data *data);

//	grammar_check.c
int						check_empty_or_whitespace(char *str);
int						valid_quotes(char *str);
void					update_token_quote_status(t_token *token);
int						len_between_tokens(char *str, int i, char c);
int						len_invalid_type(char *str);

// heredoc.c
void					unlink_heredoc(t_data *data);
int						handle_heredoc(t_token *tmp, t_data *data,
							int option);

//	lex.c
int						lexer(t_data *data);

//	redir_types.c
int						get_type(char *str);
void					set_redirection_types(t_token *tokens);

//	remove_quotes.c
void					remove_quotes(t_token *tokens);

//	string_utils.c
char					*get_value_after_expansion(char *str, t_data *data,
							int *i);

//	syntax_check.c
int						validate_heredoc_syntax(t_token *tokens, t_data *data);
int						check_syntax(t_token *tokens, t_data *data);

////////////////////////// PARSING ////////////////////////////

// create_command.c
t_cmd					*get_command(t_token *tokens);
void					add_command_back(t_cmd **commands,
							t_cmd *new_node);

//	parse.c
char					**convert_tokens_to_cmd_array(t_token *tokens);
bool					is_builtin(char *cmd);
int						parsing(t_data *data);

//	redirs_utils.c
void					handle_redirections(t_token *tokens,
							t_cmd *command);

//	tokens_utils.c
t_token					*get_next_pipe(t_token *token);
int						count_not_null_tokens(t_token *tokens);

////////////////////////// BUILTINS ////////////////////////////

//	cd.c
int						ft_cd(t_cmd *commands, t_data *data);

//	echo.c
int						ft_echo(t_cmd *commands);

//	env_init.c
t_env					*init_default_env(void);
t_env					*init_env(char **env);
char					**init_env_array(t_env *env_head);

//	env_set_free.c
void					ft_free_env(t_env *env);
char					*ft_getenv(t_env *env_list, char *key);
void					ft_setenv(t_env *env_head, char *name, char *value);

//	env_utils.c
char					*get_env_value(char *str, char *var_name);
t_env					*init_env_node(char *str);
t_env					*init_default_env_node(char *var_name, char *value);
void					append_env_variable(t_env **head, t_env *new_node);

//	env.c
int						ft_env(t_data *data);

//	exit.c
void					ft_exit(t_cmd *commands, t_data *data, bool pipe);

//	export_utils.c
int						cleanup_and_return(char *curr_dir, char *old_dir, \
							int ret);
int						handle_export_error(char *curr_dir, char *old_dir);

//	export.c
int						ft_export(char **cmd, t_data *data);

//	pwd.c
int						ft_pwd(t_cmd *commands);

//	unset.c
int						check_if_variable_exists(t_env *env_head, \
							char *var_name);
int						ft_unset(char **cmd, t_data *data);

////////////////////////// EXEC ////////////////////////////

//	exec_cmd.c
void					handle_error(char *cmd, char *error, int exit_status,
							t_data *data);
char					*get_cmd_path(char *cmd, t_data *data);

//	exec_fds_utils.c
void					duplicate_fd(int fd, int new_fd, t_data *data,
							int exit_status);
void					close_fds(t_data *data);
void					close_pipe_fds(t_data *data);

//	exec_open.c
void					get_fd_in(t_token *redirections, t_data *data);
void					get_fd_out(t_token *redirections, t_data *data);

//	exec_redirs.c
void					get_fds(t_token *redirections, t_data *data);
void					open_and_redirect_fd(t_cmd *current,
							t_data *data);
void					has_no_filename(t_cmd *current, t_data *data,
							int prev_fd);

//	exec.c
int						executing(t_data *data);

//	shlvl.c
void					change_shlvl(t_data *data);

// utils.c
void					save_heredoc_line(int fd, char *tmp, t_data *data,
							int quotes);
void					pipe_and_fork(t_cmd *current, t_data *data);
void					wait_commands(t_data *data);

////////////////////////// UTILS ////////////////////////////

//	errors.c
int						syntax_error_eof(void);
int						handle_token_syntax_error(char *token, t_data *data);
void					print_error(char *cmd, char *error, char *arg);
void					print_warning(char *arg);
int						check_args(int argc);

//	free.c
void					ft_free_all_and_exit(t_data *data, int exit_code);
void					ft_free_all(t_data *data);
void					free_tokens(t_token **tokens);
void					ft_free_cmds(t_cmd **commands);

// stack_utils.c
t_token					*create_token(char *value, int type, int quotes);
void					add_token_back(t_token **tokens, t_token *new_node);
char					**init_tab(int size);

////////////////////////// SIGNALS ////////////////////////////

//	signals.c
void					catch_sigint(int signum);
void					heredoc_sigint_handler(int signum);
void					signals_handler(void);

#endif
