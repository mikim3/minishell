/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:36:56 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 15:28:27 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

t_tree_node	*ft_tree_init(int type, void *node_content)
{
	t_tree_node	*new;

	new = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (new == 0)
		return (0);
	new->type = type;
	new->content = node_content;
	new->left = 0;
	new->right = 0;
	return (new);
}

int	ft_tree_node_pre_traversal(\
	t_tree_node *target_tree, void (*function)(void *))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)target_tree);
	ft_tree_node_pre_traversal(target_tree->left, (*function));
	ft_tree_node_pre_traversal(target_tree->right, (*function));
	return (FT_SUCCESS);
}

int	ft_tree_node_post_traversal(\
	t_tree_node *target_tree, void (*function)(void *))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	ft_tree_node_post_traversal(target_tree->left, (*function));
	ft_tree_node_post_traversal(target_tree->right, (*function));
	function((t_tree_node *)target_tree);
	return (FT_SUCCESS);
}
