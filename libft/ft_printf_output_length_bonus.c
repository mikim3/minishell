/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output_length.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:22:58 by kshim             #+#    #+#             */
/*   Updated: 2022/05/01 14:43:13 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_len_of_output(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> fs == 'c')
		data -> ap_len = 1;
	else
	{
		data -> ap_len = ft_strlen(data -> processed_ap);
		if ((formats -> fs == 'd' || formats -> fs == 'i')
			&& *(data -> processed_ap) == '-')
			(data -> ap_len)--;
	}
	if (formats -> fs == 's' || formats -> fs == 'c')
		pf_chars_len(formats, data);
	else if (formats -> fs == 'd' || formats -> fs == 'i'
		|| formats -> fs == 'u' || formats -> fs == 'x'
		|| formats -> fs == 'X' || formats -> fs == 'p')
		pf_int_len(formats, data);
	if (formats -> space_sign == 1 || formats -> plus_sign == 1
		|| formats -> neg_value == 1)
		pf_sign_len(formats, data);
	if (formats -> alternate == 1 || formats -> fs == 'p')
		pf_alter_len(formats, data);
	return (1);
}

void	pf_chars_len(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> precision == 1)
	{
		if (data -> ap_len < formats -> prec_val)
			data -> output_len = data -> ap_len;
		else
		{
			data -> output_len = formats -> prec_val;
			data -> ap_len = formats -> prec_val;
		}	
	}
	else
		data -> output_len = data -> ap_len;
	if (formats -> width > data -> ap_len)
	{
		data -> width_pad = (formats -> width) - (data -> output_len);
		data -> output_len = formats -> width;
	}
	return ;
}

void	pf_int_len(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> precision == 1)
	{
		if (formats -> prec_val == 0 && *(data -> processed_ap) == '0')
		{
			data -> output_len = 0;
			data -> ap_len = 0;
		}
		else if (data -> ap_len < formats -> prec_val)
		{
			data -> output_len = formats -> prec_val;
			data -> prec_pad = (data -> output_len) - (data -> ap_len);
		}
		else
			data -> output_len = data -> ap_len;
	}
	else
		data -> output_len = data -> ap_len;
	if ((formats -> width) > (data -> output_len))
	{
		data -> width_pad = (formats -> width) - (data -> output_len);
		data -> output_len = formats -> width;
	}
	return ;
}

void	pf_sign_len(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> plus_sign == 1 || formats -> space_sign == 1
		|| formats -> neg_value == 1)
	{
		if (data -> width_pad >= 1)
			(data -> width_pad)--;
		else
			(data -> output_len)++;
	}
	return ;
}

void	pf_alter_len(t_pf_formats *formats, t_pf_str *data)
{
	if ((formats -> alternate == 1 && *(data -> processed_ap) != '0')
		|| formats -> fs == 'p')
	{
		if (data -> width_pad >= 1)
		{
			if (data -> width_pad == 1)
			{
				(data -> width_pad)--;
				(data -> output_len)++;
			}
			else if (data -> width_pad >= 2)
				data -> width_pad = (data -> width_pad) - 2;
		}
		else
			data -> output_len = (data -> output_len) + 2;
	}
	return ;
}
