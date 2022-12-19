/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:36:56 by kshim             #+#    #+#             */
/*   Updated: 2022/12/19 11:45:13 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tree.h"


#include <stdio.h>

t_tree_node	*ft_tree_init(void *node_content)
{
	t_tree_node	*new;

	new = (t_tree_node *)malloc(sizeof(tt_tree_node));
	if (new == BOOL_FALSE)
		return (FT_FAIL);
	new->content = node_content;
	return (new);
}

void	ft_tree_add_node_left(t_tree_node *target_tree, t_tree_node *new_node)
{
	if (target_tree == BOOL_FALSE)
		return ;
	if (target_tree->left != BOOL_FALSE)
	{
		// 디버깅용
		printf("left node overwrited\n");
		ft_tree_node_post_traversal(target_tree, ft_tree_delete_node());
	}
	target_tree->left = new_node;
	return ;
}

void	ft_tree_add_node_right(t_tree_node *target_tree, t_tree_node *new_node)
{
	if (target_tree == BOOL_FALSE)
		return ;
	if (target_tree->right != BOOL_FALSE)
	{
		// 디버깅용
		printf("right node overwrited\n");
		ft_tree_node_post_traversal(target_tree, ft_tree_delete_node());
	}
	target_tree->right = new_node;
	return ;
}

// 순
void	ft_tree_delete_node()
{



}

//
int	ft_tree_node_post_traversal(t_tree_node *target_tree, char(*f)(unsigned int, char))
{
	if (target_tree == BOOL_FALSE)
		return (FT_FAIL);
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	if ((*f) == BOOL_FALSE)
		return (FT_FAIL);
	return ;
}

// 읽는거
int	ft_tree_node_pre_traversal(t_tree_node *target_tree, char(*f)(unsigned int, char))
{
	if (target_tree == BOOL_FALSE)
		return (FT_FAIL);
	if ((*f) == BOOL_FALSE)
		return (FT_FAIL);
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	return ;
}





