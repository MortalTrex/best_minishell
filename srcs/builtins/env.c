#include "minishell.h"

typedef struct s_env
{
	char	*line;
	struct s_env	*next;
}	t_env;

void	ft_copy_env (char **envp)
{
	int	i;
	t_env	*env;
	t_env	*new;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env->line = ft_strdup(envp[i]);
	env->next = NULL;
	i++;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->line = ft_strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
}

void ft_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

void	ft_env(char **envp)
{
	t_env	*env;

	env = NULL;
	printf("env\n");
	ft_copy_env(envp);
	ft_print_env(env);
}
