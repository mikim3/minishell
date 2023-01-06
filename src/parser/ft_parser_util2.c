/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:55:03 by kshim             #+#    #+#             */
/*   Updated: 2023/01/06 20:55:19 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_free_a_tree_node_cmd_content(t_tree_node *node)
{
	t_tree_cmd		*cmd_content;

	cmd_content = (t_tree_cmd *)node->content;
	if (cmd_content == 0)
		return ;
	if (cmd_content->cmd_name != 0)
		free(cmd_content->cmd_name);
	cmd_content->cmd_name = 0;
	ft_free_string_ptr_arr(cmd_content->cmd_argv);
	cmd_content->cmd_argv = 0;
	free(cmd_content);
	cmd_content = 0;
}

void	ft_free_a_tree_node_redir_content(t_tree_node *node)
{
	t_tree_rdr		*redir_content;

	redir_content = (t_tree_rdr *)node->content;
	if (redir_content == 0)
		return ;
	if (redir_content->redir != 0)
		free(redir_content->redir);
	redir_content->redir = 0;
	if (redir_content->file_name != 0)
		free(redir_content->file_name);
	redir_content->file_name = 0;
	free(redir_content);
	redir_content = 0;
	return ;
}
