/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:58:20 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/02/28 16:05:14 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredoc(t_data *data)
{
	if (unlink(data->heredoc) == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}
}

static void	create_filename(t_data *data)
{
	char	*temp_file;
	int		fd;
	char	*temp_num;

	temp_num = ft_itoa(getpid() + 1);
	temp_file = ft_strjoin("/tmp/minishell_heredoc_", temp_num);
	free(temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin");
		free(temp_file);
		return ;
	}
	fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		free(temp_file);
		perror("open");
		return ;
	}
	close(fd);
	data->heredoc = temp_file;
}

static void	cleanup_heredoc(int fd, t_data *data)
{
	if (fd != -1)
		close(fd);
	close(STDIN_FILENO);
	dup2(data->stdin_old, STDIN_FILENO);
	close(data->stdin_old);
}

static void	create_heredoc(char *delimiter, t_data *data, int quote_status)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(data->heredoc, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (perror("open"));
	signal(SIGINT, heredoc_sigint_handler);
	while (g_exit_status != 130)
	{	
		line = readline("> ");
		if ((line && ft_strcmp(line, delimiter) == 0))
			break ;
		if (line == NULL)
		{
			if (g_exit_status != 130)
				print_warning(delimiter);
			break ;
		}
		tmp = line;
		save_heredoc_line(fd, tmp, data, quote_status);
	}
	if (line)
		free(line);
	cleanup_heredoc(fd, data);
}

int	handle_heredoc(t_token *tmp, t_data *data, int option)
{
	int	ret;

	ret = 0;
	data->stdin_old = dup(STDIN_FILENO);
	if (option == 0)
		ret = validate_heredoc_syntax(data->tokens, data);
	if (data->heredoc)
		free(data->heredoc);
	create_filename(data);
	signal(SIGINT, heredoc_sigint_handler);
	create_heredoc(tmp->value, data, tmp->quotes);
	if (!data->heredoc)
		return (1);
	return (ret);
}
