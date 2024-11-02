/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/11/03 00:15:11 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig, t_data *data)
{
	(void)sig;
	ft_free_all(data);
	exit(SIGINT);
}

// Launch CONTROL C
static void	sigint_handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
