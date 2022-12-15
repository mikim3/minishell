/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:42:22 by kshim             #+#    #+#             */
/*   Updated: 2022/05/01 14:44:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"

void	pf_put_str(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		write(1, (str + i), 1);
		i++;
	}
	return ;
}

int	pf_check_fs(char *arg)
{
	if (*arg == 'c' || *arg == 's' || *arg == 'p' || *arg == 'd'
		|| *arg == 'i' || *arg == 'u' || *arg == 'x' || *arg == 'X')
		return (1);
	return (0);
}

char	*pf_set_c(t_pf_formats *formats)
{
	char	*tmp;
	char	c;

	tmp = (char *)malloc(2);
	if (tmp == NULL)
		return (NULL);
	c = (char)va_arg(*formats -> ap, int);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}
