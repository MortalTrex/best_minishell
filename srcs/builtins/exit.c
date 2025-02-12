/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:15 by rbalazs           #+#    #+#             */
/*   Updated: 2025/02/12 15:44:42 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long my_atoll(const char *str)
{
    int i = 0;
    int sign = 1;
    long long result = 0;
    
    
    if (str[i] == '+' || str[i] == '-') // Handle sign
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    
    while (str[i])
    {
        int digit = str[i] - '0';
        
        // Overflow check before adding the digit
        if (result > (LLONG_MAX / 10) || 
            (result == (LLONG_MAX / 10) && digit > (LLONG_MAX % 10)))
            return (0);
        result = result * 10 + digit;
        i++;
    }
    return (result * sign);
}

bool	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (my_atoll(str) > LLONG_MAX || my_atoll(str) < LLONG_MIN)
		return (false);
	return (true);
}

int	ft_value(int value)
{
	if (value > 255 || value < 0)
		value = (value % 256 + 256) % 256;
	return (value);
}

static void	ft_exit_one_argument(t_data *data, char **argv)
{
	int	value;

	value = 0;
	if (ft_is_number(argv[1]))
	{
		value = ft_atoi(argv[1]);
		value = ft_value(value);
		ft_free_all(data);
		exit(value);
	}
	else
		ft_error(data, "exit: numeric argument required\n");
}

void	ft_exit(char **argv, t_data *data)
{
	dup2(data->stdin_backup, STDIN_FILENO);
	close(data->stdin_backup);
	dup2(data->stdout_backup, STDOUT_FILENO);
	close(data->stdout_backup);
	if (argv[1] && !ft_is_number(argv[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		ft_free_all(data);
		exit(2);
	}
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		exit(1);
		return ;
	}
	if (argv[1])
		ft_exit_one_argument(data, argv);
	else
	{
		ft_free_all(data);
		exit(0);
	}
}
