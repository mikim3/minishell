/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:51:56 by kshim             #+#    #+#             */
/*   Updated: 2022/12/15 15:19:48 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tokenizer.h"

int	ft_is_quote(char cha)
{
	if (cha == '\'' || cha == '\"')
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

int	ft_can_become_operator(char diff_target, char cha, int token_len)
{
	if (token_len > 1)
		return (BOOL_FALSE);
	if (diff_target != '|' && diff_target == cha)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

int	ft_is_operator(char cha)
{
	if (cha == '<' || cha == '>' || cha == '|')
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}
