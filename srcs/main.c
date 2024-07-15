#include "../inc/minishell.h"


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


int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;

	char *line;
	//t_data data;
	//data.cmds->argv = argv;

	// READ COMMANDS
	while (true)
	{
		line = readline("minishell> ");

		// printf("%s\n", line);

		//execute(data);
		ft_echo(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
	}
	return (0);
}