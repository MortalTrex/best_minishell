/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list_expand_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:15:53 by mmiilpal          #+#    #+#             */
/*   Updated: 2024/12/06 22:26:03 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_initialize_work_variable(t_replace_variables *work,
		const char *str, t_data *data)
{
	ft_bzero(work, sizeof(t_replace_variables));
	work->len = ft_strlen(str);
	work->result = malloc(work->len + 1);
	if (!work->result)
		ft_error_exit(data, ERR_MALLOC);
	work->res_ptr = work->result;
	work->ptr = str;
	return (true);
}

static bool	ft_char_in_expand_variable(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')
		|| (c >= '0' && c <= '9'));
}

static void	ft_append_variable_value(t_replace_variables *work)
{
	if (work->var_value)
	{
		work->value_len = ft_strlen(work->var_value);
		ft_memcpy(work->res_ptr, work->var_value, work->value_len);
		work->res_ptr += work->value_len;
	}
}

static char	*ft_replace_variable(const char *str, t_data *data)
{
	t_replace_variables	work;

	ft_initialize_work_variable(&work, str, data);
	while (*work.ptr)
	{
		if (*work.ptr == '$')
		{
			work.ptr++;
			work.start = work.ptr;
			while (*work.ptr && ft_char_in_expand_variable(*work.ptr))
				work.ptr++;
			work.var_len = work.ptr - work.start;
			work.var_name = ft_strndup(work.start, work.var_len);
			work.var_value = ft_get_env_value(work.var_name, data);
			free(work.var_name);
			ft_append_variable_value(&work);
		}
		else
			*work.res_ptr++ = *work.ptr++;
	}
	*work.res_ptr = '\0';
	return (work.result);
}

void	ft_expand_values_in_tokens(t_data *data)
{
	t_token	*current;
	char	*expanded_value;

	current = data->tok;
	expanded_value = NULL;
	while (current)
	{
		if (current->to_expand)
		{
			expanded_value = ft_replace_variable(current->value, data);
			free(current->value);
			current->value = expanded_value;
		}
		current = current->next;
	}
}
