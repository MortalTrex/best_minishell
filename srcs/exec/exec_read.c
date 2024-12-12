#include "minishell.h"


void    ft_read_commands(t_shell_list *node, t_data *data)
{
	t_shell_list *current;
	int i;

	i = 0;
	current = node;
	while (current)
	{
		ft_multi_pipe(current, data, i);
		current = current->next;
		i++;
	}
}

void	ft_execution(t_data *data)
{
	if (!data->shell_list)
		return ;
	ft_count_levels(data->shell_list, 0, data);
	ft_read_redirs(data->shell_list, data);
	ft_read_heredoc(data->shell_list, data);
	if (data->nb_levels == 0)
		ft_no_pipe(data->shell_list, data);
	else if (data->nb_levels >= 1)
		ft_read_commands(data->shell_list, data);
	ft_erase_all_temp_here_doc(data->shell_list);
}
