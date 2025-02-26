// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   debug.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/25 14:19:54 by mmiilpal          #+#    #+#             */
// /*   Updated: 2025/02/26 14:44:22 by mmiilpal         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	print_ast(t_ast_node *node, int level)
// {
// 	t_redir	*redir;
// 	int		i;
// 	int		j;

// 	if (!node)
// 		return ;
// 	i = -1;
// 	while (++i < level)
// 		printf("  ");
// 	printf("Node Type: ");
// 	if (node->type == NODE_CMD)
// 	{
// 		printf("Command\n");
// 		printf("Command: %s\n", node->command);
// 		printf("Arguments:\n");
// 		i = -1;
// 		while (node->argv && node->argv[++i])
// 		{
// 			j = -1;
// 			while (++j < level + 1)
// 				printf("  ");
// 			printf("%s\n", node->argv[i]);
// 		}
// 		redir = node->redir;
// 		while (redir)
// 		{
// 			i = -1;
// 			while (++i < level + 1)
// 				printf("  ");
// 			printf("Redirection: %s %s\n", redir->file,
// 				redir->type == IN ? "<" : redir->type == OUT ? ">" :
// 				redir->type == D_APPEND ? ">>" : "<<");
// 			redir = redir->next;
// 		}
// 	}
// 	else if (node->type == NODE_PIPE)
// 		printf("Pipe\n");
// 	else
// 		printf("Unknown\n");
// 	if (node->left)
// 	{
// 		i = -1;
// 		while (++i < level)
// 			printf("  ");
// 		printf("Left Child:\n");
// 		print_ast(node->left, level + 1);
// 	}
// 	if (node->right)
// 	{
// 		i = -1;
// 		while (++i < level)
// 			printf("  ");
// 		printf("Right Child:\n");
// 		print_ast(node->right, level + 1);
// 	}
// }

// void	print_tab(char **str)
// {
// 	int	i;

// 	if (!str)
// 		return ;
// 	i = 0;
// 	while (str[i])
// 	{
// 		ft_printf("%s", str[i]);
// 		i++;
// 	}
// }

// //char					*remove_char(char *str, char c);
// //char					*get_env_from_str(char *str);
// //char					*get_new_str_value(char *str, char *old_value,char *new_value, int prev_index);
// //int						invalid_type_syntax_error(t_token *token, t_shell *shell);
// //t_command				*init_command(void);
// //t_command				*get_last_command(t_command *head);
// //int						is_valid_identifier(char *str);
// //int						check_if_other_heredoc(t_token *current);
// //void					free_line(char *line, t_token *tmp);

// // int						init_shell(t_shell *shell, char **env);
// // int						minishell_loop(t_shell *shell);