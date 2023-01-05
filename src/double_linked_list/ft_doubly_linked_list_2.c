/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_linked_list_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:30:11 by kshim             #+#    #+#             */
/*   Updated: 2022/12/30 09:20:09 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_deque_add_back(t_detower *detower, t_d_list *new_elem)
{
	if (new_elem == 0)
		return ;
	new_elem -> prev = 0;
	new_elem -> next = 0;
	if (detower -> head == 0)
		detower -> head = new_elem;
	else
	{
		detower -> tail -> next = new_elem;
		new_elem -> prev = detower -> tail;
	}
	detower -> tail = new_elem;
	detower -> tail -> next = 0;
	return ;
}

void	ft_deque_add_front(t_detower *detower, t_d_list *new_elem)
{
	if (new_elem == 0)
		return ;
	new_elem -> prev = 0;
	new_elem -> next = 0;
	if (detower -> head == 0)
	{
		detower -> head = new_elem;
		detower -> tail = new_elem;
	}
	else
	{
		new_elem -> next = detower -> head;
		detower -> head -> prev = new_elem;
		detower -> head = new_elem;
	}
	detower -> head -> prev = 0;
	return ;
}

void	ft_deque_del_back(t_detower *detower, void (*delete)(void *))
{
	t_d_list	*tmp;

	tmp = detower -> tail;
	if (detower -> tail == 0)
		return ;
	if (detower -> tail -> prev == 0)
	{
		detower -> head = 0;
		detower -> tail = 0;
	}
	else
	{
		detower -> tail -> prev -> next = 0;
		detower -> tail = detower -> tail -> prev;
	}
	tmp -> next = 0;
	tmp -> prev = 0;
	ft_d_lstdelone(tmp, (*delete));
	return ;
}

void	ft_deque_del_front(t_detower *detower, void (*delete)(void *))
{
	t_d_list	*tmp;

	tmp = detower -> head;
	if (detower -> head == 0)
		return ;
	if (detower -> head -> next == 0)
	{
		detower -> head = 0;
		detower -> tail = 0;
	}
	else
	{
		detower -> head -> next -> prev = 0;
		detower -> head = detower -> head -> next;
	}
	tmp -> next = 0;
	tmp -> prev = 0;
	ft_d_lstdelone(tmp, (*delete));
	return ;
}
