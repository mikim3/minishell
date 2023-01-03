/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 15:27:20 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	next_pipe_check(t_tree_node *node,t_pipe *m_pipe)
{
	// 다음노드가 존재하고 다음노드의 타입이 파이프일떄
	// ex) bash-3.2$ echo hahhahh | echo vvfsdv --> 화면출력 vvfsdv
	// 이 경우 echo hahhahh 는 출력이 안돼야함
	// if (node->right != NULL && node->right->type == NODE_PIPELINE)
	if (node->right != NULL && node->right->type == NODE_PIPELINE)
	{
		if (pipe(m_pipe->pipe) < 0)
		{
			ft_putendl_fd("PIPE ERROR", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		m_pipe->next_pipe_check = BOOL_TRUE;
	}
	else
	{
		m_pipe->next_pipe_check = BOOL_FALSE;
	}
	return ;
}

void	ft_execute_tree(t_tree_node *node,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	// printf("ft_execute_tree \n");
	printf("ft_execute_tree node->type == %d ----\n",node->type);
	// if (node->type == NODE_PIPELINE) 
	// {
	// 	next_pipe_check(node,m_pipe);
	// 	printf("ft_execute_tree in NODE_PIPELINE\n");
	// }
	if (node->type == NODE_REDIRECTIONS)
	{
		if (node->left == 0)
			return ;
		printf("ft_execute_tree in NODE_REDIRECTIONS\n");
	}
	else if (node->type == NODE_REDIR) //REDIRECTIONS랑 헷갈림
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

// 실행전에 infile_fd와 outfile_fd가 설정한대로 표준출력과 표준입력을 나타내게끔 바꾼다.
void	init_pipe_in_execute(t_pipe *m_pipe)
{
	if (m_pipe->infile_fd != STDIN_FILENO) // 만약 infile_fd STDIN_FILENO가 아니면
		dup2(STDIN_FILENO, m_pipe->infile_fd);			//  m_pipe->infile_fd STDIN_FILENO의 역할을 하게끔 바뀐다.
	if (m_pipe->outfile_fd != STDOUT_FILENO)
		dup2(STDOUT_FILENO, m_pipe->outfile_fd);		//  outfile_fd가 표준출력대신 출력되게끔 한다. 
}
