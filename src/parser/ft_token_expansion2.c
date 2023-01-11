/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:04:36 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 15:52:30 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_expand_expansion_sign(t_expand *expand, t_d_list *mnsh_envp)
{
	expand->len = 0;
	expand->start = ++expand->pos;
	if ((*expand->pos) == '?')
	{
		expand->len++;
		expand->pos++;
		if (ft_token_expand_str_control_with_expand(&(expand->ret_str),
				expand->start, expand->len, mnsh_envp) == FT_ERROR)
			return (FT_ERROR);
		expand->start = expand->pos;
		expand->len = 0;
		return (FT_SUCCESS);
	}
	while (ft_token_expand_is_char_expendable((*expand->pos)) == FT_SUCCESS)
	{
		expand->len++;
		expand->pos++;
	}
	if (ft_token_expand_str_control_with_expand(&(expand->ret_str),
			expand->start, expand->len, mnsh_envp) == FT_ERROR)
		return (FT_ERROR);
	expand->start = expand->pos;
	expand->len = 0;
	return (FT_SUCCESS);
}

int	ft_token_expand_double_quotes(
		t_expand *expand, t_d_list *mnsh_envp, int expand_mode)
{
	expand->len = 0;
	expand->start = ++expand->pos;
	while ((*expand->pos) != '\"')
	{
		if ((expand_mode == EXPAND_ALL) && (*expand->pos) == '$')
		{
			if (ft_token_expand_str_control_without_expand(
					&(expand->ret_str), expand->start, expand->len) == FT_ERROR)
				return (FT_ERROR);
			if (ft_token_expand_expansion_sign(
					expand, mnsh_envp) == FT_ERROR)
				return (FT_ERROR);
		}
		else
		{
			expand->len++;
			expand->pos++;
		}
	}
	if (ft_token_expand_str_control_without_expand(
			&(expand->ret_str), expand->start, expand->len) == FT_ERROR)
		return (FT_ERROR);
	expand->start = ++expand->pos;
	expand->len = 0;
	return (FT_SUCCESS);
}

int	ft_token_expand_single_quotes(t_expand *expand)
{
	expand->len = 0;
	expand->start = ++expand->pos;
	while ((*expand->pos) != '\'')
	{
		expand->len++;
		expand->pos++;
	}
	if (ft_token_expand_str_control_without_expand(
			&(expand->ret_str), expand->start, expand->len) == FT_ERROR)
		return (FT_ERROR);
	expand->start = ++expand->pos;
	expand->len = 0;
	return (FT_SUCCESS);
}
