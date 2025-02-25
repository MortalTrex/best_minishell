/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/25 14:24:26 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_data *data, char *msg)
{
	close(data->fd[0]);
	close(data->fd[1]);
	ft_error(data, msg);
}

void	ft_error(t_data *data, char *msg)
{
	ft_free_all(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

void	ft_error_quote(t_data *data)
{
	ft_putstr_fd("minishell> unexpected EOF while looking for matching ` or \"",
		STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
}
void	ft_heredoc_warning(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}
int	syntax_error_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
		STDERR_FILENO);
	return (1);
}

void	write_error(char *cmd, char *error, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
int	invalid_arg(int argc)
{
	if (argc != 1)
		return (write_error(NULL, "minishell doesn't take any arguments", NULL),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	syntax_error_in_token(char *token, t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	data->exit_status = 2;
	return (1);
}