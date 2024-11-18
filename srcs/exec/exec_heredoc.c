#include "minishell.h"

static void	create_filename(t_redir *redir)
{
	char	*temp_file;
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
	if (access(temp_file, F_OK) == -1)
	{
		redir->file = temp_file;
		return ;
	}
	free(temp_file);
}

static int	ft_env_var_heredoc(char *str, size_t i, int fd, t_data *data)
{
	size_t	start;
	char	*var;

	start = i++;
	if (str[i] == '?')
		return (ft_putnbr_fd(data->exit_status, fd), 2);
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	if (i != start)
	{
		var = ft_substr(str, start, i);
		if (!(var = ft_get_env_value(var, data)))
			ft_putstr_fd(var, fd);
		free(var);
	}
	return (i);

}

static void	ft_expand_heredoc(char *command,int fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			i += ft_env_var_heredoc(command, i, fd, data);
		else
			ft_putchar_fd(command[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}
static void close_hd(t_redir *redir, t_data *data)
{
	if (redir->hd_fd != -1)
		close(redir->hd_fd);
	close(STDIN_FILENO);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
}

static void	ft_read_heredoc(t_redir *redir, t_data *data)
{
	char	*line;
	char	*read;

	read = redir->file;
	redir->hd_fd = open(read, O_RDWR | O_CREAT , 0666);
	if (redir->hd_fd == -1)
		perror("heredoc");
	signal(SIGINT, heredoc_sigint_handler);
	while (*read && !ft_is_quote(*read))
		read++;
	while (g_exit_status != 130)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(redir->file, line))
			break ;
		if (!*read)
			ft_expand_heredoc(line, redir->hd_fd, data);
		else
			ft_putendl_fd(line, redir->hd_fd);
	}
	if (line)
		free(line);
	close_hd(redir, data);
}

void	ft_process_heredoc(t_redir *redir, t_data *data)
{
	data->fd[0] = dup(STDIN_FILENO);
	if (redir->file == NULL)
		create_filename(redir);
	ft_read_heredoc(redir, data);
	data->isheredoc = true;
}