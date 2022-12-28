/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_linked_list_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:56:25 by kshim             #+#    #+#             */
/*   Updated: 2022/12/28 16:46:53 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_doubly_linked_list.h"

void	ft_deque_add_prev_node(t_detower *detower,
		t_d_list *pos, t_d_list *new_elem)
{
	t_d_list	*nod;

	if (detower -> head == pos)
		ft_deque_add_front(detower, new_elem);
	else
	{
		nod = pos -> prev;
		pos -> prev = new_elem;
		new_elem -> prev = nod;
		new_elem -> next = pos;
		nod -> next = new_elem;
	}
	return ;
}

void	ft_deque_add_next_node(t_detower *detower,
		t_d_list *pos, t_d_list *new_elem)
{
	t_d_list	*nod;

	if (detower -> tail == pos)
		ft_deque_add_back(detower, new_elem);
	else
	{
		nod = pos -> next;
		pos -> next = new_elem;
		new_elem -> next = nod;
		new_elem -> prev = pos;
		nod -> prev = new_elem;
	}
	return ;
}

int		ft_deque_lstsize(t_detower *detower)
{
	int			iter;
	t_d_list	*node;

	iter = 0;
	if (detower == 0)
		return (iter);
	node = detower->head;
	while (node != 0)
	{
		iter++;
		node = node->next;
	}	
	return (iter);
}