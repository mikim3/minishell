/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:20:23 by kshim             #+#    #+#             */
/*   Updated: 2022/05/03 12:00:41 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"

void	pf_set_output(t_pf_formats *formats, t_pf_str *data)
{
	size_t	i;

	i = 0;
	if (formats -> zero_fill == 1 && formats -> precision == 0)
	{
		pf_set_sign_alter(formats, data, &i);
		pf_set_width_pad(formats, data);
	}
	else if (formats -> left_justify == 0)
	{
		pf_set_width_pad(formats, data);
		pf_set_sign_alter(formats, data, &i);
	}
	if (formats -> left_justify == 1)
		pf_set_sign_alter(formats, data, &i);
	pf_set_char(formats, data, &i);
	if (formats -> left_justify == 1)
		pf_set_width_pad(formats, data);
	return ;
}

void	pf_set_sign_alter(t_pf_formats *formats, t_pf_str *data, size_t *i)
{
	if (formats -> neg_value == 1)
	{
		write(1, "-", 1);
		(*i)++;
	}
	else if (formats -> plus_sign == 1 || formats -> space_sign == 1)
	{
		if (formats -> plus_sign == 1)
			write(1, "+", 1);
		else if (formats -> space_sign == 1)
			write(1, " ", 1);
	}
	if ((formats -> alternate == 1 && *(data -> processed_ap) != '0')
		|| formats -> fs == 'p')
	{
		write(1, "0", 1);
		if (formats -> fs == 'x' || formats -> fs == 'p')
			write(1, "x", 1);
		else if (formats -> fs == 'X')
			write(1, "X", 1);
	}
	return ;
}

void	pf_set_width_pad(t_pf_formats *formats, t_pf_str *data)
{
	while (data -> width_pad != 0)
	{
		if (formats -> zero_fill == 1 && formats -> precision == 0)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		(data -> width_pad)--;
	}
	return ;
}

void	pf_set_char(t_pf_formats *formats, t_pf_str *data, size_t *i)
{
	if (formats -> precision == 1)
	{
		while (data -> prec_pad != 0)
		{
			write(1, "0", 1);
			(data -> prec_pad)--;
		}
	}
	while (data -> ap_len != 0)
	{
		write(1, ((data -> processed_ap) + *i), 1);
		(*i)++;
		(data -> ap_len)--;
	}
	return ;
}
