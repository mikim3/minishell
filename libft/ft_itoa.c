/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:41:46 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 11:12:32 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	how_long(int n);
static void	distribute_char(char *str, int n, int len);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = how_long(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	str[len] = '\0';
	distribute_char(str, n, len);
	return (str);
}

static int	how_long(int n)
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
		temp = temp / 10;
		len++;
	}
	return (len);
}

static void	distribute_char(char *str, int n, int len)
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
		str[i--] = (temp % 10) + '0';
		temp = temp / 10;
	}
}
