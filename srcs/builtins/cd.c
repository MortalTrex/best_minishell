/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:07 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/27 15:30:16 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_value(t_data *data, char *command)
{
	char	cwd[4096];
	char	*old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(command);
		return ;
	}
	old_dir = ft_getenv(data->env, "PWD");
	if (!old_dir)
		return ;
	ft_setenv(data->env, "OLDPWD", old_dir);
	free(old_dir);
	ft_setenv(data->env, "PWD", cwd);
}

static int	ft_move_directoy(t_data *data, int option)
{
	char	*curr_dir;
	char	*old_dir;

	curr_dir = ft_getenv(data->env, "OLDPWD");
	old_dir = ft_getenv(data->env, "PWD");
	if (!curr_dir)
	{
		print_error("cd", "OLDPWD not set", NULL);
		return (cleanup_and_return(curr_dir, old_dir, 1));
	}
	else if (!old_dir)
	{
		print_error("cd", "PWD not set", NULL);
		return (cleanup_and_return(curr_dir, old_dir, 1));
	}
	if (curr_dir && chdir(curr_dir) == -1)
		return (handle_export_error(curr_dir, old_dir));
	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_setenv(data->env, "PWD", curr_dir);
	ft_setenv(data->env, "OLDPWD", old_dir);
	return (cleanup_and_return(curr_dir, old_dir, 0));
}

static int	check_for_arguments(t_cmd *cmds, t_data *data)
{
	if (cmds->cmd_args[1])
	{
		if (cmds->cmd_args[1][0] == '-' && !cmds->cmd_args[1][1])
			return (ft_move_directoy(data, 1));
		else if (cmds->cmd_args[1][0] == '-'
			&& cmds->cmd_args[1][1] == '-' && !cmds->cmd_args[1][2])
			return (ft_move_directoy(data, 0));
		else if (cmds->cmd_args[1][0] == '-' && cmds->cmd_args[1][1])
		{
			print_error("cd", "invalid option", cmds->cmd_args[1]);
			return (2);
		}
		else if (chdir(cmds->cmd_args[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			perror(cmds->cmd_args[1]);
			return (EXIT_FAILURE);
		}
		update_pwd_value(data, cmds->cmd_args[1]);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_cmd *cmds, t_data *data)
{
	char	*value;

	if (cmds->cmd_args[0] && cmds->cmd_args[1] && cmds->cmd_args[2])
	{
		print_error("cd", "too many arguments", NULL);
		return (EXIT_FAILURE);
	}
	if (!cmds->cmd_args[1])
	{
		value = ft_getenv(data->env, "HOME");
		if (!value)
			return (print_error("cd", "HOME not set", NULL), free(value), 1);
		if (!ft_strlen(value))
		{
			free(value);
			value = getcwd(NULL, 0);
		}
		if (chdir(value) == -1)
			return (perror("minishell: cd:"), free(value), EXIT_FAILURE);
		update_pwd_value(data, cmds->cmd_args[0]);
		free(value);
	}
	return (check_for_arguments(cmds, data));
}
