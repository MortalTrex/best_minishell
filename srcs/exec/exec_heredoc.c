/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:04:45 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/11/03 19:58:56 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_var_heredoc(char *str, size_t i, int fd, t_data *data)
{
	size_t	start;
	char	*var;

	start = i++;
	if (str[i] == '?')
		return (ft_putnbr_fd(data->exit_status, fd), 2);
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	if (i != start)
	{
		var = ft_substr(str, start, i);
		if (!(var = ft_get_env_value(var, data)))
			ft_putstr_fd(var, fd);
		free(var);
	}
	return (i);

}

static void	ft_expand_heredoc(char *command,int fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			i += ft_env_var_heredoc(command, i, fd, data);
		else
			ft_putchar_fd(command[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}

static void	ft_read_heredoc(t_redir *redir, int *fd, t_data *data)
{
	char	*line;
	char	*read;


	signal(SIGINT, heredoc_sigint_handler);
	read = redir->command;
	while (*read && !ft_is_quote(*read))
		read++;
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(redir->command, line))
			break ;
		if (!*read)
			ft_expand_heredoc(line, fd[1], data);
		else
			ft_putendl_fd(line, fd[1]);
	}
	ft_free_all(data);
	exit(0);
}
static bool ft_heredoc_signal(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, sigquit_handler);
	g_signals.child_signal = false;
	close(fd[1]);
	if (WEXITSTATUS(*pid) == SIGINT && WIFEXITED(*pid))
		return (true);
	return (false);
}
void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	int			fd[2];
	pid_t		pid;

	pipe(fd);
	g_signals.child_signal = true;
	if (!(pid = (signal(SIGQUIT, SIG_IGN), fork())))
		ft_read_heredoc(redir, fd, data);
	if (ft_heredoc_signal(fd, &pid))
		return ;
	redir->hd_fd = fd[0];

}
