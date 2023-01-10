/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_analysis2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:11:08 by kshim             #+#    #+#             */
/*   Updated: 2023/01/10 15:15:50 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_stx_a_cmd_prefix(t_list *token_list, t_list *token, int token_pos, \
	char **err_token)
{
	token_pos = ft_stx_a_redir(token_list, token, token_pos, err_token);
	if (token_pos == -1)
		return (-1);
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_type(token) == TKN_NULL
		|| ft_token_type(token) == TKN_PIPE)
		return (token_pos);
	if (ft_token_type(token) != TKN_WORD)
	{
		token_pos = ft_stx_a_cmd_prefix(\
			token_list, token, token_pos, err_token);
		if (token_pos == -1)
			return (-1);
	}
	return (token_pos);
}

int	ft_stx_a_cmd_suffix(t_list *token_list, t_list *token, int token_pos, \
	char **err_token)
{
	if (ft_token_type(token) == TKN_NULL)
		return (token_pos);
	else if (ft_token_type(token) == TKN_WORD)
	{
		token_pos = ft_stx_a_word(token_list, token, token_pos, err_token);
		if (token_pos == -1)
			return (-1);
	}
	else
	{
		token_pos = ft_stx_a_redir(token_list, token, token_pos, err_token);
		if (token_pos == -1)
			return (-1);
	}
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_type(token) == TKN_NULL
		|| ft_token_type(token) == TKN_PIPE)
		return (token_pos);
	token_pos = ft_stx_a_cmd_suffix(token_list, token, token_pos, err_token);
	if (token_pos == -1)
		return (-1);
	return (token_pos);
}

int	ft_stx_a_redir(t_list *token_list, t_list *token, int token_pos, \
	char **err_token)
{
	token = ft_lst_num(token_list, token_pos);
	if (ft_token_type(token) == TKN_REDIRECT
		|| ft_token_type(token) == TKN_FD_REDIRECT)
	{
		token_pos = ft_stx_a_word(\
			token_list, token->next, token_pos + 1, err_token);
		if (token_pos == -1)
			return (-1);
	}
	else
	{
		*err_token = ft_token_str(token);
		return (-1);
	}
	return (token_pos);
}

int	ft_stx_a_word(t_list *token_list, t_list *token, int token_pos, \
	char **err_token)
{
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_type(token) == TKN_NULL)
	{
		*err_token = ft_token_str(token);
		return (-1);
	}
	if (ft_token_type(token) != TKN_WORD)
	{
		*err_token = ft_token_str(token);
		return (-1);
	}
	return (token_pos + 1);
}
