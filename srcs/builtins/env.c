/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:32:12 by rbalazs           #+#    #+#             */
/*   Updated: 2024/09/02 17:41:50 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env *ft_copy_env_node(char *str)
// {
// 	t_env *env = malloc(sizeof(t_env));
// 	env->line = ft_strdup(str);
// 	env->next = NULL;
// 	return env;
	
// }

// t_env *ft_copy_env(char **envp)
// {
// 	t_env *env = NULL;
// 	t_env *current = NULL; // Initialize current to NULL
// 	int i = 0;
	
// 	while (envp[i])
// 	{
// 		t_env *new_env = ft_copy_env_node(envp[i]); // Create a new node
		
// 		if (env == NULL) // If env is empty, set new_env as the head
// 		{
// 			env = new_env;
// 			current = new_env;
// 		}
// 		else // Otherwise, add new_env to the end of the list
// 		{
// 			current->next = new_env;
// 			current = new_env;
// 		}

// 		i++;
// 	}
	
// 	return env; // Return the head of the list
// }

t_env *new_node_env(char *line)
{
	t_env *new_node = malloc(sizeof(t_env));
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	return new_node;
}

void push_node_to_env(t_env **env, char *line)
{
	t_env *new_node = new_node_env(line);

	if (*env == NULL)
		*env = new_node;
	else
	{
		t_env *current = *env;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void ft_print_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s\n", env->line);
		env = env->next;
	}
}

void ft_find_pwd(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->line, "PWD", 3) == 0)
		{
			ft_printf("\033[0;31m%s\n\033[0m", env->line + 4);
			break ;
		}
		env = env->next;
	}
}

void ft_env(char **envp)
{
	t_env *env = NULL;

	int i = 0;
	while(envp[i])
	{
		push_node_to_env(&env, envp[i]);
		i++;
	}
	char *str = "Variable1=Marie a faim";

	push_node_to_env(&env, str);
	ft_print_env(env);
	ft_find_pwd(env);
}
