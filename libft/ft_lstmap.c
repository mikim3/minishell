/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:26:40 by kshim             #+#    #+#             */
/*   Updated: 2022/03/24 09:16:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*temp;

	new_head = ft_lstnew(f(lst -> content));
	if (new_head == NULL)
		return (NULL);
	temp = new_head;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		temp -> next = ft_lstnew(f(lst -> content));
		if (temp == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		temp = temp -> next;
	}
	return (new_head);
}
