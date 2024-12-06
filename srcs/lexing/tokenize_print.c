/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:31:57 by rbalazs           #+#    #+#             */
/*   Updated: 2024/12/06 22:55:53 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_choose_type_2(t_token_type type)
{
	if (type == T_INFILE)
		return "T_INFILE";
	else if (type == T_REDIR_OUT)
		return "T_REDIR_OUT";
	else if (type == T_OUTFILE)
		return "T_OUTFILE";
	else if (type == T_REDIR_APPEND)
		return "T_REDIR_APPEND";
	else if (type == T_APPENDFILE)
		return "T_APPENDFILE";
	else if (type == T_REDIR_HERE)
		return "T_REDIR_HERE";
	else if (type == T_DELIMITER)
		return "T_DELIMITER";
	else
		return "UNKNOWN";
}

static char *ft_choose_type(t_token_type type)
{
	if (type == T_CMD)
		return "T_CMD";
	else if (type == T_ARG)
		return "T_ARG";
	else if (type == T_PIPE)
		return "T_PIPE";
	else if (type == T_ASSIGN)
		return "T_ASSIGN";
	else if (type == T_VARIABLE)
		return "T_VARIABLE";
    else if (type == T_VALUE_VAR)
        return "T_VALUE_VAR";
	else if (type == T_REDIR_IN)
		return "T_REDIR_IN";
	else
		return ft_choose_type_2(type);
}

void ft_print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	printf("%sPrinting Tokens %s\n", RED, RESET);
	while (current)
	{
		printf("%svalue: %s - %s", BLUE, current->value, RESET);
		char *type_str = ft_choose_type(current->type);
		printf("%s type: %s - ", GREEN, type_str);
        if (current->to_expand)
            printf("to_expand: %strue\n%s", RED, RESET);
        else
            printf("to_expand: %sfalse\n%s", RED, RESET);
		current = current->next;
	}
}
