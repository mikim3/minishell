/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:23:15 by kshim             #+#    #+#             */
/*   Updated: 2022/12/19 14:25:14 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_num(t_list *lst, int num)
{
	int	i;

	if (lst == NULL)
		return (NULL);
	i = 1;
	while (lst -> next != NULL && i < num)
	{
		lst = lst -> next;
		i++;
	}
	return (lst);
}
