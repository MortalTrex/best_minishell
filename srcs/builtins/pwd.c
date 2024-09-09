/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:21 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/09 10:02:10 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("Error PWD");
	else
	{
		ft_printf("%s\n", pwd);
		free(pwd);
	}
}
