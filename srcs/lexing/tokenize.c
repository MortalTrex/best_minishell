/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 18:49:11 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_found_token_in_argv(t_data *data)
{
	char *prompt;

    if (ft_check_if_quotes_closes(data) == false)
            return (ft_error_quote(data), false);
	prompt = ft_strdup(data->user_line);
	prompt = add_spaces_around_tokens(prompt);
    prompt = replace_spaces_in_quotes(prompt);
	data->tok = fill_list_tokens(prompt);
	if (!data->tok)
		return (free(prompt), false);
	free(prompt);
    if (check_errors_in_tokens(data->tok))
            return (ft_putstr_fd("minishell: syntax error\n", 2), free_tokens(&data->tok), false);
	return (true);
}
