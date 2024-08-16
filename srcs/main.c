#include "../inc/minishell.h"

// void ft_commands()
// {

// }

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;

	char *line;
	//t_data data;

	// READ COMMANDS
	while (true)
	{
		line = readline("minishell> ");

		// printf("%s\n", line);

		//data = parser(line);

		//execute(data);
		ft_echo(line);
		if (ft_strncmp(line, "exit", 4) == 0)

		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
	}
	return (0);
}
