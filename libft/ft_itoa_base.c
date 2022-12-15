/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:48:51 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:38:44 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	how_long(int n, int base);
static void	distribute_char(char *str, int n, int len, int base);
static char	process_num_base(int num, int base);

char	*ft_itoa_base(int n, int base)
{
	char	*str;
	int		len;

	if (base != 10 && base != 16)
		return (0);
	len = how_long(n, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	str[len] = '\0';
	distribute_char(str, n, len, base);
	return (str);
}

static int	how_long(int n, int base)
{
	int	len;
	int	temp;

	len = 0;
	temp = n;
	if (temp == 0)
		len++;
	if (temp == -2147483648)
	{
		len++;
		temp = -214748364;
	}
	if (temp < 0)
	{
		len++;
		temp = -1 * temp;
	}
	while (temp != 0)
	{
		temp = temp / base;
		len++;
	}
	return (len);
}

static void	distribute_char(char *str, int n, int len, int base)
{
	int	temp;
	int	i;

	temp = n;
	i = len - 1;
	if (temp == 0)
		str[0] = '0';
	if (temp == -2147483648)
	{
		str[i--] = '8';
		temp = -214748364;
	}
	if (temp < 0)
	{
		str[0] = '-';
		temp = -1 * temp;
	}
	while (temp != 0)
	{
		str[i--] = process_num_base(temp % base, base);
		temp = temp / base;
	}
}

static char	process_num_base(int num, int base)
{
	char	c;

	c = 0;
	if (base == 10)
		c = num + '0';
	else if (base == 16)
	{
		if (num >= 0 && num <= 9)
			c = num + '0';
		else if (num >= 10 && num <= 15)
			c = (char)(num + 87);
	}
	return (c);
}
