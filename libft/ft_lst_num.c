/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:23:15 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 12:02:51 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_num(t_list *lst, int num)
{
	int	i;

	if (lst == 0)
		return (0);
	i = 1;
	while (i < num)
	{
		if (lst == 0)
			return (0);
		lst = lst->next;
		i++;
	}
	return (lst);
}
