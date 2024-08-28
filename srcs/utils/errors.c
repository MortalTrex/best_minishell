#include "minishell.h"

void	ft_perror_msg(char *msg, int *fd)
{
	if (fd != NULL)
	{
		close(fd[0]);
		close(fd[1]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

// void ft_free_all(t_data *data)
// {
// 	ft_free_tokens(data->tokens);
// }
