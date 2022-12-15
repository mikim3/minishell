/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:05:37 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:46:07 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	how_long(unsigned int n, int base);
static char	*distribute_char(unsigned int n, int len, int base, int upper);
static char	process_num_base(unsigned int num, int base, int upper);

char	*ft_uitoa_base(unsigned int n, int base, int upper)
{
	char	*str;
	int		len;

	if (base != 10 && base != 16)
		return (0);
	len = how_long(n, base);
	str = distribute_char(n, len, base, upper);
	if (str == 0)
		return (0);
	return (str);
}

static int	how_long(unsigned int n, int base)
{
	int				len;
	unsigned int	temp;

	len = 0;
	temp = n;
	if (temp == 0)
		len++;
	while (temp != 0)
	{
		temp = temp / base;
		len++;
	}
	return (len);
}

static char	*distribute_char(unsigned int n, int len, int base, int upper)
{
	char			*str;
	unsigned int	temp;
	int				i;

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
		str[i--] = process_num_base(temp % base, base, upper);
		temp = temp / base;
	}
	return (str);
}

static char	process_num_base(unsigned int num, int base, int upper)
{
	char	c;

	c = 0;
	if (base == 10)
		c = num + '0';
	else if (base == 16)
	{
		if (num <= 9)
			c = num + '0';
		else if (num >= 10 && num <= 15)
		{
			if (upper == 0)
				c = (char)(num + 87);
			else if (upper == 1)
				c = (char)(num + 55);
		}
	}
	return (c);
}
