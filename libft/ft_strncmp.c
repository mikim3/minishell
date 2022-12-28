/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:35:25 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:45:55 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		a = s1[i];
		b = s2[i];
		if ((a - b) > 0)
			return (1);
		else if ((a - b) < 0)
			return (-1);
		i++;
	}
	if (s2[i] != '\0' && i < n)
		return (-1);
	return (0);
}
