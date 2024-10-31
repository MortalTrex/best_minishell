#include "minishell.h"

void	ft_detect_builtin(t_data *data)
{
	t_token	*current;

	current = data->tok;
	while (current)
	{
		if (current->type == T_WORD)
		{
			if (!ft_strcmp(current->value, "cd"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				ft_cd(data);
				return ;
			}
			else if (!ft_strcmp(current->value, "echo"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				current->type = T_BUILTIN;
				ft_echo(data);
			}
			else if (!ft_strcmp(current->value, "pwd"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				ft_pwd();
			}
			else if (!ft_strcmp(current->value, "export"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				ft_export(data);
			}
			else if (!ft_strcmp(current->value, "unset"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				ft_unset(data);
			}
			else if (!ft_strcmp(current->value, "env"))
			{
				printf("\033[0;31mdetect_builtin\033[0m\n");
				ft_env(data);
			}
			else if (!ft_strcmp(current->value, "exit"))
				ft_exit(data);
		}
		if (current)
			current = current->next;
	}
}