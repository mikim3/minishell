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
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (s1[i] != '\0')
	{
		a = s1[i];
		b = s2[i];
		if ((a - b) > 0)
			return (1);
		else if ((a - b) < 0)
			return (-1);
		i++;
	}
	if (s2[i] != '\0')
		return (-1);
	return (0);
}
