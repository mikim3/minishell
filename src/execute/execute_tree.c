/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/28 13:15:04 by mikim3           ###   ########.fr       */
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
		// exe_cmd_set cmd_argv를 이용해서 그 위치에 t_exe_cmd를 넣어야 되겠다.
		
		// exe_cmd_set(((t_tree_cmd *)node->content)->cmd_argv, char *input);
		// exe_cmd_set(node)


		execute_cmd(node,dll_envp_tower,m_pipe);
	}
	if (node->type == NODE_SIMPLE_CMD)
	{
		printf("ft_execute_tree in NODE_SIMPLE_CMD ----\n");
		// execute_cmd(node, dll_envp_tower,m_pipe);
	}
}


// void ft_execute_tree()



