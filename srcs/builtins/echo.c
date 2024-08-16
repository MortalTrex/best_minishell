#include "minishell.h"

void ft_echo(char *line)
{
	char *res;

	int i = 0;
	int len = 0;
	int start = 0;
	if (line[i] == 'e' && line[i + 1] == 'c' && line[i + 2] == 'h' && line[i + 3] == 'o')
	{
		i = 4;
		start = 4;
		while (line[i] == ' ')
		{
			i++;
			start++;
		}
		while (line[i])
		{
			len++;
			i++;
		}
	}
	res = malloc(sizeof(char) * len + 1);
	i = 0;
	while (line[start])
	{
		res[i] = line[start];
		i++;
		start++;
	}
	res[i] = '\0';
	ft_printf("%s\n", res);
	free(res);
}
