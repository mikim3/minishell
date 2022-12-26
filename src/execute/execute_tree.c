/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 16:08:56 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

// NODE_PIPELINE = 0,
// NODE_SIMPLE_CMD,
// NODE_REDIRECTIONS,
// NODE_CMD,
// NODE_REDIR,
// NODE_FD_REDIR,

void    next_pipe_check(t_tree_node *token_tree,t_pipe *m_pipe)
{

}


void    ft_execute_tree(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
    // printf("ft_execute_tree \n");
    printf("ft_execute_tree token_tree->type == %d\n",token_tree->type);
    if (token_tree->type == NODE_PIPELINE) 
    {
        next_pipe_check(token_tree,m_pipe);
    }
    if (token_tree->type == NODE_REDIR) //REDIRECTIONS랑 헷갈림
    {
        // 리다이렉션
    }
    if (token_tree->type == NODE_CMD)
    {
        printf("ft_execute_tree in NODE_CMD\n");
    }
    if (token_tree->type == NODE_SIMPLE_CMD)
    {
        printf("ft_execute_tree in NODE_SIMPLE_CMD\n");
		execute_cmd(token_tree,dll_envp_tower,m_pipe);
    }
}

void    ft_execute_tree_node(void *tree_node)
{
    t_tree_node     *node;
    t_tree_cmd      *cmd_content;
    t_tree_redir    *redir_content;
    t_pipe          *m_pipe;
    t_detower       *dll_envp_tower;
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


// void	ft_free_a_tree_node(void *target)
// {
// 	t_tree_node		*node;
// 	t_tree_cmd 		*cmd_content;
// 	t_tree_redir	*redir_content;
	
// 	node = (t_tree_node *)target;
// 	if (node == 0)
// 		return ;
// 	if (node->type == NODE_CMD)
// 	{
// 		cmd_content = (t_tree_cmd *)node->content;
// 		if (cmd_content->cmd_name != 0)
// 			free(cmd_content->cmd_name);
// 		cmd_content->cmd_name = 0;
// 		ft_free_string_ptr_arr(cmd_content->cmd_argv);
// 		cmd_content->cmd_argv = 0;
// 		free(cmd_content);
// 		cmd_content = 0;
// 	}
// 	else if (node->type == NODE_REDIR || node->type == NODE_FD_REDIR)
// 	{
// 		redir_content = (t_tree_redir *)node->content;
// 		free(redir_content->redir);
// 		redir_content->redir = 0;
// 		free(redir_content->file_name);
// 		redir_content->file_name = 0;
// 		free(redir_content);
// 		redir_content = 0;
// 	}
// 	node->type = 0;
// 	node->left = 0;
// 	node->right = 0;
// 	free(node);
// 	return ;
// }

// void	test_tree_node_check_for_content(void *tree_node)
// {
// 	t_tree_node *node;
// 	int	i;

// 	i = 0;
// 	node = (t_tree_node *)tree_node;
// 	if (node->type == NODE_CMD)
// 	{
// 		if (node->content == 0)
// 			return ;
// 		printf("node_cmd_name : %s\n", ((t_tree_cmd *)node->content)->cmd_name);
// 		while (((t_tree_cmd *)node->content)->cmd_argv[i] != 0)
// 		{
// 			printf("node_cmd_argv : %s\n", ((t_tree_cmd *)node->content)->cmd_argv[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	else if (node->type == NODE_REDIR
// 		|| node->type == NODE_FD_REDIR)
// 	{
// 		if (node -> content == 0)
// 			return ;
// 		printf("node_redir : %s\n", ((t_tree_redir *)node->content)->redir);
// 		printf("node_file_name : %s\n", ((t_tree_redir *)node->content)->file_name);
// 	}
// 	return ;
// }



// void ft_execute_tree()



