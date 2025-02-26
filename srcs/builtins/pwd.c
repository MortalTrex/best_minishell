/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:21 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 18:36:24 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_pwd(t_cmd *commands)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Error PWD");
		return (1);
	}
	else if (commands->cmd_args[1] && commands->cmd_args[1][0]
		&& commands->cmd_args[1][0] == '-')
	{
		print_error(commands->cmd_args[1], "invalid option", NULL);
		return (2);
	}
	else
	{
		printf("%s\n", pwd);
		ft_free((void **)&pwd);
	}
	return (0);
}
