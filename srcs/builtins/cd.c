/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2024/10/10 17:13:26 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data)
{
	t_token	*current;

	current = data->tok;
	current = current->next;
	// if (current)
	// 	current = current->next;
	printf("current->value: %s\n", current->value);
	// rl_on_new_line();
	// rl_replace_line("current", 0);
	// rl_redisplay();
}
