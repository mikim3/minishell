/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:20:30 by kshim             #+#    #+#             */
/*   Updated: 2022/06/07 13:17:04 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_printf_formats{
	va_list		*ap;
	size_t		width;
	int			alternate;
	int			zero_fill;
	int			left_justify;
	int			plus_sign;
	int			space_sign;
	int			neg_value;
	int			precision;
	size_t		prec_val;
	char		fs;
}		t_pf_formats;

typedef struct s_printf_str_data{
	size_t		width_pad;
	size_t		prec_pad;
	size_t		ap_len;
	size_t		output_len;
	char		*processed_ap;
}		t_pf_str;

int				ft_printf(const char *arg, ...);
t_pf_formats	*pf_set_formats(va_list *ap);
t_pf_str		*pf_set_data(void);
void			pf_del_data(t_pf_str **data);
void			pf_del_formats(t_pf_formats **formats);
int				pf_check_flags(char **arg, t_pf_formats *formats);
int				pf_is_flags(char *arg, t_pf_formats *formats, int *check);
int				pf_is_width(char *arg,
					t_pf_formats *formats, int *check);
int				pf_is_precision(char *arg,
					t_pf_formats *formats, int *check);
int				pf_is_flags_error(t_pf_formats *formats);
int				pf_process_output(t_pf_formats *work_formats, int *how_many);
int				pf_make_fs_output(t_pf_formats *formats,
					t_pf_str *data, int *how_many);
int				pf_process_char_ap(t_pf_formats *formats, t_pf_str *data);
int				pf_process_int_ap(t_pf_formats *formats, t_pf_str *data);
int				pf_process_uint_ap(t_pf_formats *formats, t_pf_str *data);
void			pf_set_output(t_pf_formats *formats, t_pf_str *data);
void			pf_set_sign_alter(t_pf_formats *formats,
					t_pf_str *data, size_t *i);
void			pf_set_width_pad(t_pf_formats *formats, t_pf_str *data);
void			pf_set_char(t_pf_formats *formats, t_pf_str *data,
					size_t *i);
int				pf_len_of_output(t_pf_formats *formats, t_pf_str *data);
void			pf_chars_len(t_pf_formats *formats, t_pf_str *data);
void			pf_int_len(t_pf_formats *formats, t_pf_str *data);
void			pf_sign_len(t_pf_formats *formats, t_pf_str *data);
void			pf_alter_len(t_pf_formats *formats, t_pf_str *data);
void			pf_put_str(char *str, size_t len);
int				pf_check_fs(char *arg);
char			*pf_set_c(t_pf_formats *formats);

#endif
