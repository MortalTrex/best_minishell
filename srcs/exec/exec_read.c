#include "minishell.h"

void	ft_execution(t_data *data)
{
	t_token	*current;
	char	*cmd;
	int		i;

	i = 0;
	current = data->tok;
	while (current)
	{
		if (current->type == T_WORD && i == 0)
		{
			if (exec_onecommand(current->value, data) == -1)
				ft_error(data, "Error: exec failed\n");
			cmd = ft_strdup(current->value);
		}
		if (current-> type == T_PIPE)
		{
			printf("current->value: %s\n", current->value);
			exec_pipe(cmd, current->next->value, data);
			free(cmd);
		}
		if (current)
			current = current->next;
		i++;
	}
}
