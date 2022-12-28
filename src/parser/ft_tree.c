/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:36:56 by kshim             #+#    #+#             */
/*   Updated: 2022/12/27 14:53:23 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_tree.h"
#include "../../include/ft_tokenizer.h"
#include "../../include/ft_minishell.h"
#include <stdio.h>

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

int	ft_tree_node_pre_traversal(t_tree_node *target_tree, void (*function)(void *))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)target_tree);
	ft_tree_node_pre_traversal(target_tree->left,(*function));
	ft_tree_node_pre_traversal(target_tree->right,(*function));
	return (FT_SUCCESS);
}

int	ft_tree_node_pre_traversal2(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe, void (*function)(void *,t_detower *,t_pipe *))
{
	if (token_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)token_tree,(t_detower *)dll_envp_tower,(t_pipe *)m_pipe);
	ft_tree_node_pre_traversal2(token_tree->left, dll_envp_tower, m_pipe, (*function));
	ft_tree_node_pre_traversal2(token_tree->right, dll_envp_tower, m_pipe, (*function));
	return (FT_SUCCESS);
}


int	ft_tree_node_pre_traversal_exe_cmd_set(t_tree_node *target_tree, char *input, void (*function)(void *, char *))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)target_tree, input);
	ft_tree_node_pre_traversal_exe_cmd_set(target_tree->left, input, (*function));
	ft_tree_node_pre_traversal_exe_cmd_set(target_tree->right, input, (*function));
	return (FT_SUCCESS);
}


int	ft_tree_node_post_traversal(t_tree_node *target_tree, void (*function)(void *))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	ft_tree_node_post_traversal(target_tree->left,(*function));
	ft_tree_node_post_traversal(target_tree->right,(*function));
	function((t_tree_node *)target_tree);
	return (FT_SUCCESS);
}

/*

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
		return (FT_ERROR);
	if ((*f) == BOOL_FALSE)
		return (FT_ERROR);
	(*f)();
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	return (FT_SUCCESS);
}

// 후위 탐색
int	ft_tree_node_post_traversal(t_tree_node *target_tree, char(*f)(unsigned int, char))
{
	if (target_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*f) == BOOL_FALSE)
		return (FT_ERROR);
	ft_tree_node_traversal(target_tree->left,(*f));
	ft_tree_node_traversal(target_tree->right,(*f));
	(*f)();
	return (FT_SUCCESS);
}

// 삭제
void	ft_tree_delete_node()
{



}

*/