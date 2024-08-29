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
void	ft_msg_free_exit(char *msg, t_token **tokens)
{
	ft_stackclear(tokens);
	perror(msg);
}
