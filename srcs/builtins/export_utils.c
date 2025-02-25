/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:56:36 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/25 15:10:36 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_return(char *curr_dir, char *old_dir, int ret)
{
	if (curr_dir)
		free(curr_dir);
	if (old_dir)
		free(old_dir);
	return (ret);
}

int	handle_chdir_error(char *curr_dir, char *old_dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(old_dir);
	return (free_and_return(curr_dir, old_dir, 1));
}
