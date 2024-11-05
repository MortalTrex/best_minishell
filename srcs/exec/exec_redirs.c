#include "minishell.h"

// int	ft_process_redirections(t_ast_node *node)
// {
// 	t_redir	*redirs;
// 	int		status;

// 	redirs = node->redir;
// 	while(redirs)
// 	{
// 		if (redirs->type == T_REDIR_IN)
// 			return(ft_process_infile(redirs));
// 		else if (redirs->type == T_REDIR_OUT)
// 			return(ft_process_outfile(redirs));
// 		else if (redirs->type == T_REDIR_APPEND)
// 			return(ft_process_append(redirs));
// 		else if(redirs->type == T_REDIR_HERE)
// 			(dup2(redirs->hd_fd, 0), close(redirs->hd_fd));
// 		redirs = redirs->next;
// 	}
// 	return (1); // handle error statuses
// }
