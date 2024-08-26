#include "minishell.h"

void	ft_stackadd_back(t_token **stack, t_token *new)
{
	t_token	*last;

	last = ft_stacklast(*stack);
	if (!last)
		*stack = new;
	last->next = new;
}

t_token	*ft_stacknew(int type, void *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*ft_stacklast(t_token *stack)
{
	t_token	*tmp;
	if (!stack)
		return (NULL);
	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_stackclear(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free((*stack));
		*stack = tmp;
	}
}
