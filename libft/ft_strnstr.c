/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:44:59 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:55:42 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (str[i] == to_find[0])
		{
			while (to_find[j] != '\0' && i + j < len)
			{
				if (str[i + j] == to_find[j])
					j++;
				else
					break ;
			}
			if (to_find[j] == '\0')
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
