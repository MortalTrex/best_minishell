/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/06 22:52:12 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == IN)
			printf("Type: IN\n");
		else if (redir->type == OUT)
			printf("Type: OUT\n");
		else if (redir->type == D_APPEND)
			printf("Type: D_APPEND\n");
		else if (redir->type == D_HEREDOC)
			printf("Type: D_HEREDOC\n");
		printf("File: %s\n", redir->value);
		redir = redir->next;
	}
}

void	ft_print_shell_list(t_shell_list *shell_list)
{
	t_shell_list	*current;
	char			**argv_temp; 
	int				i;

	current = shell_list;
	printf("%sPrinting Shell List %s\n", RED, RESET);
	i = 0;
    printf("%sPrinting Shell List %s\n", RED, RESET);
	while (current)
	{
		printf("%sCommand %d: %s%s\n", BLUE, i, current->command, RESET);
		printf("%sArgv: ", GREEN);

		
		argv_temp = current->argv;
		while (argv_temp && *argv_temp)
		{
			printf("%s ", *argv_temp);
			argv_temp++;
		}
		printf("\n%s", RESET);
		printf("%sRedirs:\n", YELLOW);
		ft_print_redirs(current->redir);
		printf("%s", RESET);
		current = current->next;
		i++;
	}
}
