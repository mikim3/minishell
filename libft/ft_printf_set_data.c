/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:43:13 by kshim             #+#    #+#             */
/*   Updated: 2022/05/01 16:39:14 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_process_output(t_pf_formats *formats, int *how_many)
{
	t_pf_str		*str_data;

	str_data = pf_set_data();
	if (str_data == NULL)
		return (-1);
	if (pf_make_fs_output(formats, str_data, how_many) == -1)
	{
		*how_many = -1;
		pf_del_data(&str_data);
		return (-1);
	}
	*how_many = *how_many + str_data -> output_len;
	pf_del_data(&str_data);
	return (1);
}

int	pf_make_fs_output(t_pf_formats *formats, t_pf_str *data, int *how_many)
{
	int				ret;
	size_t			pf_ret;

	if (formats -> fs == 'c' || formats -> fs == 's')
		ret = pf_process_char_ap(formats, data);
	else if (formats -> fs == 'd' || formats -> fs == 'i')
		ret = pf_process_int_ap(formats, data);
	else
		ret = pf_process_uint_ap(formats, data);
	if (ret == -1)
		return (-1);
	pf_len_of_output(formats, data);
	pf_ret = data -> output_len + *how_many;
	if (pf_ret > 2147483647)
		return (-1);
	pf_set_output(formats, data);
	return (1);
}

int	pf_process_char_ap(t_pf_formats *formats, t_pf_str *data)
{
	char	*str;

	str = NULL;
	if (formats -> fs == 's')
	{
		str = va_arg(*formats -> ap, char *);
		if (str == NULL)
			data -> processed_ap = ft_strdup("(null)");
		else
			data -> processed_ap = ft_strdup(str);
	}
	else if (formats -> fs == 'c')
		data -> processed_ap = pf_set_c(formats);
	if (data -> processed_ap == NULL)
		return (-1);
	return (1);
}

int	pf_process_int_ap(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> fs == 'd' || formats -> fs == 'i')
		data -> processed_ap = ft_itoa_base(
				va_arg(*formats -> ap, int), 10);
	if (data -> processed_ap == NULL)
		return (-1);
	if ((data -> processed_ap)[0] == '-')
		formats -> neg_value = 1;
	return (1);
}

int	pf_process_uint_ap(t_pf_formats *formats, t_pf_str *data)
{
	if (formats -> fs == 'u')
		data -> processed_ap = ft_uitoa_base(
				va_arg(*formats -> ap, unsigned int), 10, 0);
	else if (formats -> fs == 'x')
		data -> processed_ap = ft_uitoa_base(
				va_arg(*formats -> ap, unsigned int), 16, 0);
	else if (formats -> fs == 'X')
		data -> processed_ap = ft_uitoa_base(
				va_arg(*formats -> ap, unsigned int), 16, 1);
	else if (formats -> fs == 'p')
		data -> processed_ap = ft_uintptr_to_a(
				va_arg(*formats -> ap, uintptr_t), 0);
	if (data -> processed_ap == NULL)
		return (-1);
	return (1);
}
