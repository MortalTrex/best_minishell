/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/26 15:41:59 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_data *data, char *command)
{
	char	cwd[4096];
	char	*old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(command);
		return ;
	}
	old_dir = ft_getenv(data->env_list, "PWD");
	if (!old_dir)
		return ;
	ft_setenv(data->env_list, "OLDPWD", old_dir);
	free(old_dir);
	ft_setenv(data->env_list, "PWD", cwd);
}

static int	cd_minus(t_data *data, int option)
{
	char	*curr_dir;
	char	*old_dir;

	curr_dir = ft_getenv(data->env_list, "OLDPWD");
	old_dir = ft_getenv(data->env_list, "PWD");
	if (!curr_dir)
	{
		print_error("cd", "OLDPWD not set", NULL);
		return (free_and_return(curr_dir, old_dir, 1));
	}
	else if (!old_dir)
	{
		print_error("cd", "PWD not set", NULL);
		return (free_and_return(curr_dir, old_dir, 1));
	}
	if (curr_dir && chdir(curr_dir) == -1)
		return (handle_chdir_error(curr_dir, old_dir));
	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_setenv(data->env_list, "PWD", curr_dir);
	ft_setenv(data->env_list, "OLDPWD", old_dir);
	return (free_and_return(curr_dir, old_dir, 0));
}

static int	check_for_arguments(t_cmd *commands, t_data *shell)
{
	if (commands->cmd_args[1])
	{
		if (commands->cmd_args[1][0] == '-' && !commands->cmd_args[1][1])
			return (cd_minus(shell, 1));
		else if (commands->cmd_args[1][0] == '-'
			&& commands->cmd_args[1][1] == '-' && !commands->cmd_args[1][2])
			return (cd_minus(shell, 0));
		else if (commands->cmd_args[1][0] == '-' && commands->cmd_args[1][1])
		{
			print_error("cd", "invalid option", commands->cmd_args[1]);
			return (2);
		}
		else if (chdir(commands->cmd_args[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			perror(commands->cmd_args[1]);
			return (1);
		}
		update_pwd(shell, commands->cmd_args[1]);
	}
	return (0);
}

int	ft_cd(t_cmd *commands, t_data *shell)
{
	char	*value;

	if (commands->cmd_args[0] && commands->cmd_args[1] && commands->cmd_args[2])
	{
		print_error("cd", "too many arguments", NULL);
		return (1);
	}
	if (!commands->cmd_args[1])
	{
		value = ft_getenv(shell->env_list, "HOME");
		if (!value)
			return (print_error("cd", "HOME not set", NULL), free(value), 1);
		if (ft_strlen(value) == 0)
		{
			free(value);
			value = getcwd(NULL, 0);
		}
		if (chdir(value) == -1)
			return (perror("minishell: cd:"), free(value), 1);
		update_pwd(shell, commands->cmd_args[0]);
		free(value);
	}
	return (check_for_arguments(commands, shell));
}
