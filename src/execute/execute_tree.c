/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 22:06:19 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

// NODE_PIPELINE = 0,
// NODE_SIMPLE_CMD,
// NODE_REDIRECTIONS,
// NODE_CMD,
// NODE_REDIR,
// NODE_FD_REDIR,

void	next_pipe_check(t_tree_node *token_tree,t_pipe *m_pipe)
{

}

void	ft_execute_tree(t_tree_node *node,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	// printf("ft_execute_tree \n");
	printf("ft_execute_tree node->type == %d ----\n",node->type);
	if (node->type == NODE_PIPELINE) 
	{
		next_pipe_check(node,m_pipe);
		printf("ft_execute_tree in NODE_PIPELINE\n");
	}
	if (node->type == NODE_REDIRECTIONS)
	{
		printf("ft_execute_tree in NODE_REDIRECTIONS\n");
	}
	if (node->type == NODE_REDIR) //REDIRECTIONS랑 헷갈림
	{
		printf("ft_execute_tree in NODE_REDIR\n");
		// 리다이렉션
	}
	if (node->type == NODE_CMD)
	{
		printf("ft_execute_tree in NODE_CMD\n");
		

		execute_cmd(node,dll_envp_tower,m_pipe);
	}
	if (node->type == NODE_SIMPLE_CMD)
	{
		printf("ft_execute_tree in NODE_SIMPLE_CMD ----\n");
		// execute_cmd(node, dll_envp_tower,m_pipe);
	}
}

// ((t_tree_cmd *)token_tree->content)->cmd_name 처럼 t_tree_cmd안에 있는걸 simple_cmd에 넣는다.
	
void	ft_execute_tree_node(void *tree_node)
{
	t_tree_node	 *node;
	t_tree_cmd	  *cmd_content;
	t_tree_redir	*redir_content;
	t_pipe		  *m_pipe;
	t_detower	   *dll_envp_tower;
	// printf("ft_execute_tree \n");

	node = (t_tree_node *)tree_node;
	printf("node->type == %d\n", node->type);
	if (node->type == NODE_PIPELINE) 
	{
		printf("ft_execute_tree_node in NODE_PIPELINE\n");
		// next_pipe_check(token_tree,m_pipe);
	}
	if (node->type == NODE_REDIR) //REDIRECTIONS랑 헷갈림
	{
		printf("ft_execute_tree_node in NODE_REDIR\n");
		// 리다이렉션
	}
	if (node->type == NODE_CMD)
	{
		printf("ft_execute_tree_node in NODE_CMD\n");
	}
	if (node->type == NODE_SIMPLE_CMD)
	{
		printf("ft_execute_tree in NODE_SIMPLE_CMD\n");
		execute_cmd(node,dll_envp_tower,m_pipe);
	}
}



// void ft_execute_tree()



