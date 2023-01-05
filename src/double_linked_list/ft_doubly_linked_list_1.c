/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_linked_list_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:07:29 by kshim             #+#    #+#             */
/*   Updated: 2022/12/30 09:20:07 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

t_detower	*ft_dequetower(void)
{
	t_detower	*new_detower;

	new_detower = (t_detower *)malloc(sizeof(t_detower));
	if (new_detower == 0)
		return (0);
	new_detower -> head = 0;
	new_detower -> tail = 0;
	return (new_detower);
}

t_d_list	*ft_d_lstnew(void *content)
{
	t_d_list	*new_list;

	new_list = (t_d_list *)malloc(sizeof(t_d_list));
	if (new_list == 0)
		return (0);
	new_list -> content = content;
	new_list -> prev = 0;
	new_list -> next = 0;
	return (new_list);
}

void	ft_free_detower(t_detower **detower, void (*delete)(void *))
{
	t_d_list	*lst;

	lst = (*detower)-> head;
	if (lst != 0)
		ft_d_lstclear(&lst, delete);
	(*detower)-> head = 0;
	(*detower)-> tail = 0;
	free((*detower));
	(*detower) = 0;
	return ;
}

void	ft_d_lstclear(t_d_list **lst, void (*delete)(void *))
{
	t_d_list	*now;

	now = 0;
	while (*lst != 0)
	{
		now = (*lst)-> next;
		ft_d_lstdelone(*lst, delete);
		*lst = now;
	}
	*lst = 0;
	return ;
}

void	ft_d_lstdelone(t_d_list *lst, void (*delete)(void *))
{
	if (lst -> content != 0 && delete != 0)
		delete(lst -> content);
	if (lst != 0)
		free(lst);
	return ;
}
