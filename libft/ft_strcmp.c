/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:45:20 by kshim             #+#    #+#             */
/*   Updated: 2022/06/24 16:47:15 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s1_uc;
	const unsigned char	*s2_uc;
	size_t				i;

	s1_uc = (const unsigned char *)s1;
	s2_uc = (const unsigned char *)s2;
	i = 0;
	while (s1_uc[i] && s2_uc[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1_uc[i] != s2_uc[i])
			break ;
		i++;
	}
	return ((int)(s1_uc[i] - s2_uc[i]));
}
