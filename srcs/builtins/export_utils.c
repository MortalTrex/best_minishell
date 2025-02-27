/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:56:36 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 15:28:34 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cleanup_and_return(char *curr_dir, char *old_dir, int ret)
{
	if (curr_dir)
		free(curr_dir);
	if (old_dir)
		free(old_dir);
	return (ret);
}

int	handle_export_error(char *curr_dir, char *old_dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(old_dir);
	return (cleanup_and_return(curr_dir, old_dir, 1));
}
