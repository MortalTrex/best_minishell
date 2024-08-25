/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:12:06 by rbalazs           #+#    #+#             */
/*   Updated: 2024/08/25 15:46:35 by rbalazs          ###   ########.fr       */
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
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

////////////////////////// PROTOTYPES ///////////////////////////

//Pipex
char	*find_path(char *cmd, char **envp);
void	exec(char *arg, char **envp);
void	ft_process_infile(char **argv, int *fd, char **envp);
void	ft_process_outfile(char **argv, int *fd, char **envp, int argc);

//Errors
void	ft_perror_msg(char *msg, int *fd);

//Builtins
void	ft_echo(char *line);
void	print_line(char *line, int start, int len);

#endif
