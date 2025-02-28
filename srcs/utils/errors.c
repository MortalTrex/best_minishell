/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:53 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/28 16:08:07 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *error, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

int	handle_token_syntax_error(char *token, t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	data->exit_status = 2;
	return (1);
}

int	syntax_error_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", \
		STDERR_FILENO);
	return (1);
}

void	print_warning(char *arg)
{
	ft_putstr_fd("minishell: warning: here-document delimited by \
					end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	check_args(int argc)
{
	if (argc != 1)
	{
		print_error(NULL, "minishell doesn't take any arguments", NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
