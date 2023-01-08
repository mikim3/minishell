/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 08:38:58 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 07:28:13 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_type(t_list *token)
{
	return (((t_tkn *)token->content)->type);
}

char	*ft_token_str(t_list *token)
{
	return (((t_tkn *)token->content)->str);
}

int	ft_token_is_expandable(t_list *token)
{
	return (((t_tkn *)token->content)->expandable);
}

void	ft_free_a_tree_node(void *target)
{
	t_tree_node		*node;

	node = (t_tree_node *)target;
	if (node == 0)
		return ;
	if (node->type == NODE_CMD)
		ft_free_a_tree_node_cmd_content(node);
	else if (node->type == NODE_REDIR || node->type == NODE_FD_REDIR)
		ft_free_a_tree_node_redir_content(node);
	node->type = 0;
	node->left = 0;
	node->right = 0;
	free(node);
	return ;
}
