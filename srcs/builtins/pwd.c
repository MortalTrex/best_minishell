#include "../inc/minishell.h"

/*        pwd - print name of current/working directory
 */

void	ft_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
		{
			ft_printf("%s\n", envp[i] + 4);
			break ;
		}
		i++;
	}
}
