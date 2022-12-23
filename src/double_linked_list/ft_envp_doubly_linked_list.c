/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_doubly_linked_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:00:14 by kshim             #+#    #+#             */
/*   Updated: 2022/12/23 17:26:26 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_doubly_linked_list.h"
#include "../../include/ft_tokenizer.h"
#include "../../include/ft_tree.h"
#include <stdio.h>

t_detower *ft_set_envp_dll(char **envp)
{
	t_detower		*dll_envp_tower;
	t_d_list		*new_list;
	t_envp_content	*tmp_content;
	int				iter;

	dll_envp_tower = ft_dequetower();
	if (dll_envp_tower == 0)
		return (0);
	iter = 0;
	while (envp[iter] != 0)
	{
		tmp_content = ft_set_envp_content(envp[iter]);
		if (tmp_content == 0)
		{
			ft_free_detower(&dll_envp_tower, &ft_free_t_envp_content);
			return (0);
		}
		new_list = ft_d_lstnew(tmp_content);
		if (new_list == 0)
		{
			ft_free_detower(&dll_envp_tower, &ft_free_t_envp_content);
			free(tmp_content);
			return (0);
		}
		ft_deque_add_back(dll_envp_tower, new_list);
		iter++;
	}
	return (dll_envp_tower);
}

t_envp_content	*ft_set_envp_content(char *env)
{
	t_envp_content	*new_content;

	new_content = (t_envp_content *)malloc(sizeof(t_envp_content));
	if (new_content == 0)
		return (0);
	new_content->key = ft_strdup(env);
	if (new_content->key == 0)
	{
		free(new_content);
		return (0);
	}
	new_content->value = 0;
	return (new_content);
}

// ft_free_string_ptr_arr 함수를 공용으로 만들 수 있을 것 같다. 문자열 포인터 배열을 해제하는 함수로
char	**ft_set_char_envp_from_dll(t_detower *dll_envp_tower, char **old_mnsh_envp)
{
	int			ptr_arr_len;
	char		**new_envp;
	t_d_list	*lst_node;
	int			iter;

	ptr_arr_len = ft_deque_lstsize(dll_envp_tower);
	new_envp = (char **)malloc(sizeof(char *) * (ptr_arr_len + 1));
	if (new_envp == 0)
		return (0); // 예전 envp 어떻게 처리할까? 에러 코드는 무엇일까? 동작은 어떻게 될까?
	new_envp[ptr_arr_len] = 0;
	lst_node = dll_envp_tower->head;
	iter = 0;
	while (iter < ptr_arr_len)
	{
		new_envp[iter] = ft_set_new_envp_string(lst_node);
		if (new_envp == 0)
		{
			ft_free_string_ptr_arr(new_envp);
			return (0);
		}
		lst_node = lst_node->next;
		iter++;
	}
	ft_free_string_ptr_arr(old_mnsh_envp);
	return (new_envp);
}

char	*ft_set_new_envp_string(t_d_list *lst_node)
{
	t_envp_content	*content;
	char			*ret_str;

	content = (t_envp_content *)lst_node->content;
	if (content->key == 0)
	{
		if (content->value == 0)
			return (0);
		ret_str = ft_strdup(content->value);
		if (ret_str == 0)
			return (0);
	}
	else if (content->value == 0)
	{
		ret_str = ft_strdup(content->key);
		if (ret_str == 0)
			return (0);
	}
	else
	{
		ret_str = ft_strjoin(content->key, content->value);
		if (ret_str == 0)
			return (0);
	}
	return (ret_str);	
}

void	ft_free_t_envp_content(void	*content)
{
	t_envp_content *target;
	
	target = (t_envp_content *)content;
	if (target == 0)
		return ;
	if (target->key != 0)
	{
		free(target->key);
		target->key = 0;
	}
	if (target->value != 0)
	{
		free(target->value);
		target->value = 0;
	}
	free(target);
	return ;
}
