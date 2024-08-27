#include "minishell.h"

bool	ft_isoperator(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<')
		return (true);
	return (false);
}
