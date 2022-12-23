/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintptr_to_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:45:54 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:46:15 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

static int	how_long(uintptr_t n);
static char	*distribute_char(uintptr_t n, int len, int upper);
static char	process_num_base(uintptr_t num, int upper);

char	*ft_uintptr_to_a(uintptr_t n, int upper)
{
	char	*str;
	int		len;

	len = how_long(n);
	str = distribute_char(n, len, upper);
	if (str == 0)
		return (0);
	return (str);
}

static int	how_long(uintptr_t n)
{
	int			len;
	uintptr_t	temp;

	len = 0;
	temp = n;
	if (temp == 0)
		len++;
	while (temp != 0)
	{
		temp = temp / 16;
		len++;
	}
	return (len);
}

static char	*distribute_char(uintptr_t n, int len, int upper)
{
	char		*str;
	uintptr_t	temp;
	int			i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	str[len] = '\0';
	temp = n;
	i = len - 1;
	if (temp == 0)
		str[0] = '0';
	while (temp != 0)
	{
		str[i--] = process_num_base(temp % 16, upper);
		temp = temp / 16;
	}
	return (str);
}

static char	process_num_base(uintptr_t num, int upper)
{
	char	c;

	c = 0;
	if (num <= 9)
		c = num + '0';
	else if (num >= 10 && num <= 15)
	{
		if (upper == 0)
			c = (char)(num + 87);
		else if (upper == 1)
			c = (char)(num + 55);
	}
	return (c);
}
