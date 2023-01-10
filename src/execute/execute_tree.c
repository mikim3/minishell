/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/10 14:41:38 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	next_pipe_check(t_tree_node *node, t_pipe *m_pipe)
{
	if (node->right != NULL && node->right->type == NODE_PIPELINE)
	{
		if (ft_pipe(m_pipe->pipe) < 0)
			return (FT_ERROR);
		m_pipe->next_pipe_check = BOOL_TRUE;
	}
	else
	{
		m_pipe->next_pipe_check = BOOL_FALSE;
	}
	return (FT_SUCCESS);
}

void	ft_execute_tree(t_tree_node *node, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (node->type == NODE_REDIRECTIONS)
	{
		if (node->left == 0)
			return ;
	}
	else if (node->type == NODE_REDIR || node->type == NODE_FD_REDIR)
	{
		if (node->content != 0)
			execute_redir(node, m_pipe);
	}
	else if (node->type == NODE_CMD)
	{
		if (node->content != 0)
			execute_cmd(node, dll_envp_tower, m_pipe);
	}
	return ;
}

int	ft_mnsh_tree_pre_traversal(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe, \
	void (*function)(t_tree_node *, t_detower *, t_pipe *))
{
	if (g_exit_code != 0)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)token_tree, \
		(t_detower *)dll_envp_tower, (t_pipe *)m_pipe);
	if (token_tree->left != 0)
	{
		if (ft_mnsh_tree_pre_traversal(token_tree->left, \
			dll_envp_tower, m_pipe, (*function)) == FT_ERROR)
			return (FT_ERROR);
	}
	if (token_tree->right != 0)
	{
		if (ft_mnsh_tree_pre_traversal(token_tree->right, \
			dll_envp_tower, m_pipe, (*function)) == FT_ERROR)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
