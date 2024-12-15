/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/14 21:38:50 by rbalazs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_found_token_in_argv(t_data *data)
{
	char	*prompt;
	char	*temp;

	if (ft_check_if_quotes_closes(data) == false)
		return (ft_error_quote(data), false);
	prompt = ft_strdup(data->user_line);
	temp = prompt;
	prompt = ft_add_spaces_around_tokens(prompt);
	free(temp);
	temp = prompt;
	prompt = ft_replace_spaces_in_quotes(prompt);
	free(temp);
	data->tok = ft_fill_list_tokens(prompt, data);
	if (!data->tok)
		return (free(prompt), false);
	free(prompt);
	if (ft_check_errors_in_tokens(data->tok))
		return (ft_putstr_fd("minishell: syntax error\n", 2), false);
	return (true);
}

