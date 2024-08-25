#include "minishell.h"

void	ft_stackadd_back(t_token **stack, t_token *new)
{
	if (!*(stack))
		*stack = new;
	else
		ft_stacklast(*stack)->next = new;
}

t_token	*ft_stacknew(int type, char *value)
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
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
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
