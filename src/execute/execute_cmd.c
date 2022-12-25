/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 01:09:09 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"


void excute_cmd(t_tree_node *token_tree,t_detower dll_envp_tower,t_pipe m_pipe)
{
    
    // 프린트를 안해도 되면 
	if (execute_noprint_builtin(token_tree->content, dll_envp_tower, m_pipe) == 1)
		return ;

    is_need_fork(token_tree->content); 

}

