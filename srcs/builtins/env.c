#include "minishell.h"

/*        env - run a program in a modified environment
 */

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}
