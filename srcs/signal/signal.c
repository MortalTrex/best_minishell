/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/03 17:32:32 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int sig, t_data *data)
{
	(void)sig;
	ft_free_all(data);
	exit(SIGINT);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 1);
}

// Launch CONTROL C
static void	sigint_handler(int sig, t_data *data)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(t_data *data)
{
	struct termios	terminal;

	terminal = data->terminal;
	terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	data->child_signal = false;
	data->heredoc_signal = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
