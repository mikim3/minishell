/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:38:58 by kshim             #+#    #+#             */
/*   Updated: 2022/12/30 09:19:47 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_what_type(t_list *token)
{
	return (((t_tkn *)token->content)->type);
}

char	*ft_token_what_str(t_list *token)
{
	return (((t_tkn *)token->content)->str);
}

void	ft_free_a_tree_node(void *target)
{
	t_tree_node		*node;
	t_tree_cmd 		*cmd_content;
	t_tree_rdr	*redir_content;
	
	node = (t_tree_node *)target;
	if (node == 0)
		return ;
	if (node->type == NODE_CMD)
	{
		cmd_content = (t_tree_cmd *)node->content;
		if (cmd_content->cmd_name != 0)
			free(cmd_content->cmd_name);
		cmd_content->cmd_name = 0;
		ft_free_string_ptr_arr(cmd_content->cmd_argv);
		cmd_content->cmd_argv = 0;
		free(cmd_content);
		cmd_content = 0;
	}
	else if (node->type == NODE_REDIR || node->type == NODE_FD_REDIR)
	{
		redir_content = (t_tree_rdr *)node->content;
		free(redir_content->redir);
		redir_content->redir = 0;
		free(redir_content->file_name);
		redir_content->file_name = 0;
		free(redir_content);
		redir_content = 0;
	}
	node->type = 0;
	node->left = 0;
	node->right = 0;
	free(node);
	return ;
}
