/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:38:33 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:57:46 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	deslen;

	i = 0;
	deslen = ft_strlen(dest);
	if (size <= deslen)
		return (size + ft_strlen(src));
	while (src[i] != '\0' && deslen + i + 1 < size)
	{
		dest[deslen + i] = src[i];
		i++;
	}
	if (size > 0)
		dest[deslen + i] = '\0';
	return (deslen + ft_strlen(src));
}
