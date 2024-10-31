#include "minishell.h"

bool	ft_detect_builtin(char **argv, t_data *data)
{
	(void)data;
	if (!ft_strcmp(argv[0], "cd"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		//ft_cd(argv, data);
		return(true);
	}
	else if (!ft_strcmp(argv[0], "echo"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		//ft_echo(argv, data);
	}
	else if (!ft_strcmp(argv[0], "pwd"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		ft_pwd();
	}
	else if (!ft_strcmp(argv[0], "export"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		//ft_export(argv, data);
	}
	else if (!ft_strcmp(argv[0], "unset"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		//ft_unset(argv, data);
	}
	else if (!ft_strcmp(argv[0], "env"))
	{
		printf("\033[0;31mdetect_builtin\033[0m\n");
		//ft_env(argv, data);
	}
	else if (!ft_strcmp(argv[0], "exit"))
		//ft_exit(argv, data);
		printf("\033[0;31mdetect_builtin\033[0m\n");
	else
		return (false);
	return (true);
}

// void	ft_detect_builtin(t_data *data)
// {
// 	t_token	*current;

// 	current = data->tok;
// 	while (current)
// 	{
// 		if (current->type == T_WORD)
// 		{
// 			if (!ft_strcmp(current->value, "cd"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				ft_cd(data);
// 				return ;
// 			}
// 			else if (!ft_strcmp(current->value, "echo"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				current->type = T_BUILTIN;
// 				ft_echo(data);
// 			}
// 			else if (!ft_strcmp(current->value, "pwd"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				ft_pwd();
// 			}
// 			else if (!ft_strcmp(current->value, "export"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				ft_export(data);
// 			}
// 			else if (!ft_strcmp(current->value, "unset"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				ft_unset(data);
// 			}
// 			else if (!ft_strcmp(current->value, "env"))
// 			{
// 				printf("\033[0;31mdetect_builtin\033[0m\n");
// 				ft_env(data);
// 			}
// 			else if (!ft_strcmp(current->value, "exit"))
// 				ft_exit(data);
// 		}
// 		if (current)
// 			current = current->next;
// 	}
// }