/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/11 12:55:45 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_total_commands(t_data *data)
{
	int		total_commands;
	t_token	*current;

	total_commands = 0;
	current = data->tok;
	while (current)
	{
		if (current->type == T_PIPE)
			total_commands++;
		current = current->next;
	}
	return (total_commands + 1);
}

void	ft_erase_quotes_in_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		// current->value = ft_remove_quotes(current->value);
		current = current->next;
	}
}

void	ft_parsing_tokens(t_data *data)
{
	int	total_commands;

	if (!data->tok || !data)
		return ;
	total_commands = 0;
	ft_restore_spaces_in_words(data);
	ft_check_if_expand_values(data);
	ft_expand_values_in_tokens(data);
	//ft_print_tokens(data->tok);
	ft_erase_quotes_in_tokens(data->tok);
	total_commands = ft_count_total_commands(data);
	ft_allocate_shell_list(data, total_commands);
	if (!data->shell_list)
		return ;
	ft_allocate_fill_redirs_main(data->shell_list, data);
	ft_fill_shell_list(data);
	//ft_print_shell_list(data->shell_list);
}
