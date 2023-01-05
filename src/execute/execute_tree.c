/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 12:26:59 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	next_pipe_check(t_tree_node *node,t_pipe *m_pipe)
{
	// 다음노드가 존재하고 다음노드의 타입이 파이프일떄
	// ex) bash-3.2$ echo hahhahh | echo vvfsdv --> 화면출력 vvfsdv
	// 이 경우 echo hahhahh 는 출력이 안돼야함
	// if (node->right != NULL && node->right->type == NODE_PIPELINE)
	if (node->right != NULL && node->right->type == NODE_PIPELINE)
	{
		if (ft_pipe(m_pipe->pipe) < 0)
			return (FT_ERROR);
		m_pipe->next_pipe_check = BOOL_TRUE;
	}
	else
		m_pipe->next_pipe_check = BOOL_FALSE;
	return (FT_SUCCESS);
}

void	ft_execute_tree(t_tree_node *node,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	printf("ft_execute_tree node->type == %d ----\n",node->type);
	if (node->type == NODE_REDIRECTIONS)
	{
		if (node->left == 0)
			return ;
		printf("ft_execute_tree in NODE_REDIRECTIONS\n");
	}
	else if (node->type == NODE_REDIR || node->type == NODE_FD_REDIR) //REDIRECTIONS랑 헷갈림
	{
		printf("ft_execute_tree in NODE_REDIR\n");
		execute_redir(node, m_pipe);
	}
	else if (node->type == NODE_CMD)
	{
		//init_pipe_in_execute(m_pipe);
		printf("ft_execute_tree in NODE_CMD\n");
		execute_cmd(node,dll_envp_tower,m_pipe);
	}
	else if (node->type == NODE_SIMPLE_CMD)
	{
		printf("ft_execute_tree in NODE_SIMPLE_CMD ----\n");
		// execute_cmd(node, dll_envp_tower,m_pipe);
	}
	return ;
}
