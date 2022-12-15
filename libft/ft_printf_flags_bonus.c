/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:25:48 by kshim             #+#    #+#             */
/*   Updated: 2022/05/01 14:45:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_check_flags(char **arg, t_pf_formats *formats)
{
	int				check;
	char			*tmp;

	tmp = *arg;
	check = 1;
	while (*tmp != '\0')
	{
		if (check == 1)
			pf_is_flags(tmp, formats, &check);
		if (check == 2)
			pf_is_width(tmp, formats, &check);
		if (check == 3)
			pf_is_precision(tmp, formats, &check);
		if (check == 4 || check == -1)
			break ;
		tmp++;
	}
	if (formats -> zero_fill == 1 && formats -> left_justify == 1)
		formats -> zero_fill = 0;
	if (formats -> space_sign == 1 && formats -> plus_sign == 1)
		formats -> space_sign = 0;
	formats -> fs = *tmp;
	(*arg) = tmp + 1;
	return (check);
}

int	pf_is_flags(char *arg, t_pf_formats *formats, int *check)
{
	if (*arg == '#')
		formats -> alternate = 1;
	else if (*arg == '0')
		formats -> zero_fill = 1;
	else if (*arg == '+')
		formats -> plus_sign = 1;
	else if (*arg == ' ')
		formats -> space_sign = 1;
	else if (*arg == '-')
		formats -> left_justify = 1;
	else if (*arg >= '1' && *arg <= '9')
		*check = 2;
	else if (*arg == '.')
		*check = 3;
	else if (pf_check_fs(arg) == 1)
		*check = 4;
	else
		*check = -1;
	return (1);
}

int	pf_is_width(char *arg, t_pf_formats *formats, int *check)
{
	if (*arg >= '0' && *arg <= '9')
	{
		formats -> width = (formats -> width) * 10 + ((*arg) - '0');
		if (formats -> width >= 2147483647)
			*check = -1;
	}
	else if (*arg == '.')
		*check = 3;
	else if (pf_check_fs(arg) == 1)
		*check = 4;
	else
		*check = -1;
	return (1);
}

int	pf_is_precision(char *arg, t_pf_formats *formats, int *check)
{	
	if (*arg == '.' && formats -> precision == 0)
		formats -> precision = 1;
	else if (*arg >= '0' && *arg <= '9')
	{
		formats -> prec_val
			= (formats -> prec_val) * 10 + ((*arg) - '0');
		if (formats -> prec_val >= 2147483647)
			*check = -1;
	}
	else if (pf_check_fs(arg) == 1)
		*check = 4;
	else
		*check = -1;
	return (1);
}

int	pf_is_flags_error(t_pf_formats *formats)
{
	if ((formats -> fs != 'd' && formats -> fs != 'i')
		&& (formats -> space_sign == 1))
		return (-1);
	if ((formats -> fs != 'd' && formats -> fs != 'i')
		&& (formats -> plus_sign == 1))
		return (-1);
	if ((formats -> fs == 'c' || formats -> fs == 's' || formats -> fs == 'p')
		&& formats -> zero_fill == 1)
		return (-1);
	if ((formats -> fs != 'x' && formats -> fs != 'X')
		&& formats -> alternate == 1)
		return (-1);
	if ((formats -> fs == 'c' || formats -> fs == 'p')
		&& formats -> precision == 1)
		return (-1);
	return (1);
}
