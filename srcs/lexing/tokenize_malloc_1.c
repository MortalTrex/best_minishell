/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_malloc_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 22:12:03 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_command(t_token *tokens)
{
	t_token	*current;
	bool	pipe;

	current = tokens;
	pipe = false;
	while (current)
	{
		if (current->type == T_ARG && !pipe)
		{
			current->type = T_CMD;
			pipe = true;
		}
		if (current->type == T_PIPE)
			pipe = false;
		current = current->next;
	}
}

void	ft_redir_treatement(t_fill_tokens *work, t_data *data, int *i)
{
	(*i)++;
	work->subtype = T_ARG;
	if (work->type == T_REDIR_IN)
		work->subtype = T_INFILE;
	else if (work->type == T_REDIR_OUT)
		work->subtype = T_OUTFILE;
	else if (work->type == T_REDIR_APPEND)
		work->subtype = T_APPENDFILE;
	else if (work->type == T_REDIR_HERE)
		work->subtype = T_DELIMITER;
	work->extra_token = ft_create_new_token(work->words[*i], work->subtype);
	if (!work->extra_token)
		ft_error_exit(data, ERR_MALLOC);
	work->new_token->next = work->extra_token;
	work->extra_token->prev = work->new_token;
	if (!work->last_token)
		work->last_token = work->new_token;
	else
	{
		work->last_token->next = work->new_token;
		work->new_token->prev = work->last_token;
	}
	work->last_token = work->extra_token;
}

static void	ft_add_token_to_list(t_fill_tokens **work, t_token **tokens)
{
	if (!*tokens)
		*tokens = (*work)->new_token;
	else
	{
		(*work)->last_token->next = (*work)->new_token;
		(*work)->new_token->prev = (*work)->last_token;
	}
}

static void	ft_process_tokens(t_fill_tokens *work, t_data *data, t_token **tokens)
{
	int	i;

	i = 0;
	while (work->words[i])
	{
		work->type = ft_identify_type_of_word(work->words[i]);
		work->new_token = ft_create_new_token(work->words[i], work->type);
		if (!work->new_token)
			ft_error_exit(data, ERR_MALLOC);
		if (work->type == T_REDIR_IN || work->type == T_REDIR_OUT
			|| work->type == T_REDIR_APPEND || work->type == T_REDIR_HERE)
		{
			if (work->words[i + 1])
			{
				ft_redir_treatement(work, data, &i);
				if (!*tokens)
					*tokens = work->new_token;
				i++;
				continue ;
			}
		}
		ft_add_token_to_list(&work, tokens);
		work->last_token = work->new_token;
		i++;
	}
}

t_token	*ft_fill_list_tokens(char *prompt, t_data *data)
{
	t_token			*tokens;
	t_fill_tokens	work;

	tokens = NULL;
	ft_bzero(&work, sizeof(t_fill_tokens));
	work.words = ft_split(prompt, ' ');
	if (!work.words)
		ft_error_exit(data, ERR_MALLOC);
	ft_process_tokens(&work, data, &tokens);
	ft_find_command(tokens);
	ft_free_tab(work.words);
	return (tokens);
}
