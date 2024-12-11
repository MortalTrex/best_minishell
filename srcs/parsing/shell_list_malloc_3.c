/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_malloc_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/11 09:33:21 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_argv(char **argv)
{
	size_t	count;

	count = 0;
	if (argv)
	{
		while (argv[count])
			count++;
	}
	return (count);
}

static char	**ft_append_to_argv(char **argv, char *value, t_data *data)
{
	size_t	count;
	char	**new_argv;
	size_t	i;

	i = 0;
	count = count_argv(argv);
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	while (i < count)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(value);
	if (!new_argv[count])
		ft_error_exit(data, ERR_MALLOC);
	new_argv[count + 1] = NULL;
	if (argv)
		free(argv);
	return (new_argv);
}

void	ft_fill_shell_list(t_data *data)
{
	t_shell_list *current = data->shell_list;
	t_token *current_token = data->tok;

	while (current)
	{
		while (current_token)
		{
			if (current_token->type == T_PIPE)
			{
				current_token = current_token->next;
				break ;
			}

			if (current_token->type == T_CMD)
			{
				current->command = ft_strdup(current_token->value);
				current->argv = ft_append_to_argv(current->argv,
						current_token->value, data);
			}

			if (current_token->type == T_ARG)
				current->argv = ft_append_to_argv(current->argv,
						current_token->value, data);
			current_token = current_token->next;
		}
		current = current->next;
	}
}
void	ft_free_shell_list(t_shell_list *shell_list)
{
    t_shell_list	*tmp;
    size_t			i;

    if (!shell_list)
        return ;
    while (shell_list)
    {
        tmp = shell_list;
        shell_list = shell_list->next;

        if (tmp->command != NULL)
        {
            free(tmp->command);
            tmp->command = NULL;
        }
        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
            {
                free(tmp->argv[i]);
                tmp->argv[i] = NULL;
                i++;
            }
            free(tmp->argv);
            tmp->argv = NULL;
        }
        free(tmp);
        tmp = NULL;
    }
}

// void	ft_free_shell_list(t_shell_list *head)
// {
// 	t_shell_list	*next;

// 	while (head)
// 	{
// 		next = head->next;
// 		free(head);
// 		head = next;
// 	}
// }