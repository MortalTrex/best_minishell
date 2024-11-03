/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/03 20:11:04 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	ft_free_all(*g_signals.data_pointer);
	exit(SIGINT);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 1);
}

// Launch CONTROL C
void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signals.child_signal)
	{
		ft_putstr_fd("\n", 1);
		g_signals.child_signal = false;
		g_signals.heredoc_signal = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals(t_data *data)
{
	struct termios	terminal;

	g_signals.data_pointer = &data;
	terminal = data->terminal;
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	g_signals.child_signal = false;
	g_signals.heredoc_signal = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
