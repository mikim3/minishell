/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:41:04 by kshim             #+#    #+#             */
/*   Updated: 2023/01/04 15:38:56 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/ft_tokenizer.h"

// #include <stdio.h>

#include "../../include/ft_minishell.h"

int	ft_syntax_analysis(t_list *token_list)
{
	if (ft_token_what_type(token_list) == TKN_NULL)
		return (FT_SUCCESS);
	if (ft_stx_a_pipeline(token_list, token_list, 1) == -1)
	{
		ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": syntax error near unexpected token", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_exit_code = 258;
		return (FT_ERROR);
	}
	printf("\nsyntax appropriate\n\n");
	return (FT_SUCCESS);
}

int	ft_stx_a_pipeline(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return(-1);
	if (ft_token_what_type(token) == TKN_PIPE)
		return (-1);
	token_pos = ft_stx_a_simple_cmd(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	token = ft_lst_num(token_list, token_pos);
	if (ft_token_what_type(token) == TKN_NULL)
		return (token_pos);
	if (ft_token_what_type(token) == TKN_PIPE)
	{
		token_pos = ft_stx_a_pipeline(token_list, token->next, token_pos + 1);
		if (token_pos == -1)
			return (-1);
	}
	else
		return (-1);
	return (token_pos);
}

int ft_stx_a_simple_cmd(t_list *token_list, t_list *token, int token_pos)
{
	int stack_pos;
	
	stack_pos = token_pos;
	token_pos = ft_stx_a_cmd_prefix(token_list, token, stack_pos);
	if (token_pos != -1)
	{
		stack_pos = token_pos;
		token = ft_lst_num(token_list, stack_pos);
		if (token == 0)
			return (-1);
		token_pos = ft_stx_a_word(token_list, token, stack_pos);
		if (token_pos == -1)
			return (stack_pos);
		else
		{
			stack_pos = token_pos;
			token = ft_lst_num(token_list, stack_pos);
			if (token == 0)
				return (-1);
			token_pos = ft_stx_a_cmd_suffix(token_list, token, stack_pos);
			if (token_pos == -1)
				return (stack_pos);
			else
				return (token_pos);
		}
	}
	else
	{
		token_pos = ft_stx_a_word(token_list, token, stack_pos);
		if (token_pos == -1)
			return (stack_pos);
		else
		{
			stack_pos = token_pos;
			token = ft_lst_num(token_list, stack_pos);
			if (token == 0)
				return (-1);
			token_pos = ft_stx_a_cmd_suffix(token_list, token, stack_pos);
			if (token_pos == -1)
				return (stack_pos);
			else
				return (token_pos);
		}
	}
	stack_pos = token_pos;
	return (stack_pos);
}

int ft_stx_a_cmd_prefix(t_list *token_list, t_list *token, int token_pos)
{
	token_pos = ft_stx_a_redir(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_what_type(token) == TKN_NULL)
		return (token_pos);
	if (ft_token_what_type(token) != TKN_WORD)
	{
		token_pos = ft_stx_a_cmd_prefix(token_list, token, token_pos);
		if (token_pos == -1)
			return (-1);
	}
	return (token_pos);
}

int ft_stx_a_cmd_suffix(t_list *token_list, t_list *token, int token_pos)
{
	if (ft_token_what_type(token) == TKN_NULL)
		return (token_pos);
	else if (ft_token_what_type(token) == TKN_WORD)
	{
		token_pos = ft_stx_a_word(token_list, token, token_pos);
		if (token_pos == -1)
			return (-1);
	}
	else
	{
		token_pos = ft_stx_a_redir(token_list, token, token_pos);
		if (token_pos == -1)
			return (-1);
	}
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_what_type(token) == TKN_NULL
		|| ft_token_what_type(token) == TKN_PIPE)
		return (token_pos);
	token_pos = ft_stx_a_cmd_suffix(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	return (token_pos);
}

int ft_stx_a_redir(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (ft_token_what_type(token) == TKN_REDIRECT
		|| ft_token_what_type(token) == TKN_FD_REDIRECT)
	{
		token_pos = ft_stx_a_word(token_list, token->next, token_pos + 1);
		if (token_pos == -1)
			return (-1);
	}
	else
		return (-1);
	return (token_pos);
}

int	ft_stx_a_word(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (ft_token_what_type(token) == TKN_NULL)
		return (-1);
	if (ft_token_what_type(token) != TKN_WORD)
		return (-1);
	return (token_pos + 1);
}
