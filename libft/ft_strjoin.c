/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:14:50 by kshim             #+#    #+#             */
/*   Updated: 2022/12/29 21:13:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_cat;	
	int		str_size;

	if (!s1 && !s2)
		return (NULL);
	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str_cat = (char *)malloc(sizeof(char) * str_size);
	if (!str_cat)
		return (NULL);
	ft_memcpy(str_cat, s1, ft_strlen(s1));
	ft_memcpy(str_cat + ft_strlen(s1), s2, ft_strlen(s2));
	str_cat[str_size - 1] = '\0';
	return (str_cat);
}
