/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:48:26 by kshim             #+#    #+#             */
/*   Updated: 2022/06/08 13:04:03 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;

	now = NULL;
	while (*lst != NULL)
	{
		now = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = now;
	}
	*lst = NULL;
	return ;
}
