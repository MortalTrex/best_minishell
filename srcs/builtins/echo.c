#include "../inc/minishell.h"

void	print_line(char *line, int start, int len)
{
	char	*res;
	int		i;

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

void	ft_echo(char *line)
{
	int		i;
	int		len;
	int		start;

	i = 0;
	len = 0;
	start = 0;
	if (line[i] == 'e' && line[i + 1] == 'c'
		&& line[i + 2] == 'h' && line[i + 3] == 'o')
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
	print_line(line, start, len);
}
