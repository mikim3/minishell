/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:41:42 by kshim             #+#    #+#             */
/*   Updated: 2022/03/21 15:46:58 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	x;

	i = 0;
	str = (unsigned char *)b;
	x = (unsigned char)c;
	while (i < len)
	{
		str[i] = x;
		i++;
	}
	return (b);
}	
