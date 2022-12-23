/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:53:24 by kshim             #+#    #+#             */
/*   Updated: 2022/05/01 14:47:13 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_formats	*pf_set_formats(va_list *ap)
{
	t_pf_formats	*new_formats;

	new_formats = (t_pf_formats *)malloc(sizeof(t_pf_formats));
	if (new_formats == NULL)
		return (NULL);
	new_formats -> ap = ap;
	new_formats -> width = 0;
	new_formats -> alternate = 0;
	new_formats -> zero_fill = 0;
	new_formats -> left_justify = 0;
	new_formats -> plus_sign = 0;
	new_formats -> space_sign = 0;
	new_formats -> neg_value = 0;
	new_formats -> precision = 0;
	new_formats -> prec_val = 0;
	new_formats -> fs = 0;
	return (new_formats);
}

t_pf_str	*pf_set_data(void)
{
	t_pf_str	*str_data;

	str_data = (t_pf_str *)malloc(sizeof(t_pf_str));
	if (str_data == NULL)
		return (NULL);
	str_data -> width_pad = 0;
	str_data -> prec_pad = 0;
	str_data -> ap_len = 0;
	str_data -> output_len = 0;
	str_data -> processed_ap = NULL;
	return (str_data);
}

void	pf_del_formats(t_pf_formats **formats)
{
	(*formats)-> ap = 0;
	(*formats)-> width = 0;
	(*formats)-> alternate = 0;
	(*formats)-> zero_fill = 0;
	(*formats)-> left_justify = 0;
	(*formats)-> plus_sign = 0;
	(*formats)-> space_sign = 0;
	(*formats)-> neg_value = 0;
	(*formats)-> precision = 0;
	(*formats)-> prec_val = 0;
	(*formats)-> fs = 0;
	free((*formats));
	(*formats) = NULL;
	return ;
}

void	pf_del_data(t_pf_str **data)
{
	(*data)-> width_pad = 0;
	(*data)-> prec_pad = 0;
	(*data)-> ap_len = 0;
	(*data)-> output_len = 0;
	free((*data)-> processed_ap);
	(*data)-> processed_ap = NULL;
	free(*data);
	*data = NULL;
	return ;
}
