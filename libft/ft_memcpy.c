/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:38:33 by kshim             #+#    #+#             */
/*   Updated: 2022/12/29 20:39:59 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char		*tmp;
	const char	*src_c;

	src_c = src;
	if (!len || dest == src)
		return (dest);
	tmp = dest;
	while (len--)
		*tmp++ = *src_c++;
	return (dest);
}
