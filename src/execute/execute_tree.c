/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:21:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 00:48:44 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

// NODE_PIPELINE = 0,
// NODE_SIMPLE_CMD,
// NODE_REDIRECTIONS,
// NODE_CMD,
// NODE_REDIR,
// NODE_FD_REDIR,

void    next_pipe_check(t_tree_node *token_tree,t_pipe m_pipe)
{

}


void    ft_execute_tree(t_tree_node *token_tree,t_detower dll_envp_tower,t_pipe m_pipe)
{
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
        
    }
    if (token_tree->type == NODE_SIMPLE_CMD)
    {
		excute_cmd(token_tree,dll_envp_tower,m_pipe);
    }
}

// void ft_execute_tree()



