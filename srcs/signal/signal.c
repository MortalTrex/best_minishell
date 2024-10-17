/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:37:04 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/17 13:39:05 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Launch CONTROL C
void	sigint_handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

bool	signals(t_data *data)
{
	// if (data->user_line == NULL)
    // {
    //     ft_printf("Exit\n");
	// 	return (true);
    // }
	(void)data;
	signal(SIGINT, sigint_handler);
	return(false);
}
