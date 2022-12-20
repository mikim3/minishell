/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:36:56 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 15:49:20 by kshim            ###   ########.fr       */
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

// 좌우 순서로 적절한 위치에 추가하는 함수 (이름이 존재할까?) - 함수 이름 수정 
	// 해당 노드 아래 노드들의 깊이를 기준으로 해당 깊이를 '채우도록' 할당
void	ft_tree_add_node_bfs(t_tree_node *target_tree, t_tree_node *new_node)
{
	if (target_tree->left == 0)
		target_tree->left = new_node;
	else if (target_tree->right == 0)
		target_tree->right = new_node;
	else
		ft_tree_add_node_fulfill_depth(target_tree->left, new_node);
	return ;
}


// 좌측 가지 대체
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

// 우측 가지 대체
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

// 전위 탐색
int	ft_tree_node_pre_traversal(t_tree_node *target_tree, char(*f)(unsigned int, char))
{
	if (target_tree == BOOL_FALSE)
		return (FT_FAIL);
	if ((*f) == BOOL_FALSE)
		return (FT_FAIL);
	(*f)();
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	return (FT_SUCCESS);
}

// 후위 탐색
int	ft_tree_node_post_traversal(t_tree_node *target_tree, char(*f)(unsigned int, char))
{
	if (target_tree == BOOL_FALSE)
		return (FT_FAIL);
	if ((*f) == BOOL_FALSE)
		return (FT_FAIL);
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	(*f)();
	return (FT_SUCCESS);
}

// 삭제
void	ft_tree_delete_node()
{



}
