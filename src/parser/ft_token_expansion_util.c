/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:49:18 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 16:08:50 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_check_for_quote(t_list *token)
{
	char	*str_pos;

	str_pos = ft_token_str(token);
	while (*str_pos != '\0')
	{
		if (*str_pos == '\'' || *str_pos == '\"')
		{
			return (BOOL_TRUE);
		}
		str_pos++;
	}
	return (BOOL_FALSE);
}

int	ft_token_expand_init_struct(t_expand **expand, char **token_str)
{
	*expand = (t_expand *)malloc(sizeof(t_expand));
	if (*expand == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	(*expand)->pos = *token_str;
	(*expand)->ret_str = 0;
	(*expand)->start = *token_str;
	(*expand)->len = 0;
	return (FT_SUCCESS);
}

void	ft_token_expand_free_struct(t_expand **expand)
{
	(*expand)->pos = 0;
	(*expand)->len = 0;
	(*expand)->start = 0;
	if ((*expand)->ret_str != 0)
		free((*expand)->ret_str);
	(*expand)->ret_str = 0;
	free(*expand);
	*expand = 0;
}

int	ft_token_expand_is_char_expendable(int cha)
{
	if (('a' <= cha && cha <= 'z')
		|| ('A' <= cha && cha <= 'Z')
		|| ('0' <= cha && cha <= '9')
		|| '_' == cha)
		return (FT_SUCCESS);
	return (FT_ERROR);
}
