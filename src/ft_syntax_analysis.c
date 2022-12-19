/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:41:04 by kshim             #+#    #+#             */
/*   Updated: 2022/12/19 14:54:15 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tokenizer.h"
// #include "../include/ft_tree.h"

#include <stdio.h>

int	ft_syntax_analysis(t_list *token_list)
{
	if (ft_stx_a_pipeline(token_list) == FT_SUCCESS)
	{
		// syntax 정상이니 tree 작성 시작해도 될까?
		// token_list 해제
		printf("syntax appropriate\n");
		return (FT_SUCCESS);
	}
	// syntax 에러 메시지
	// token_list 해제
	printf("syntax error\n");
	return (FT_ERROR);
}

int	ft_stx_a_pipeline(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (ft_stx_a_simple_cmd(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	if (((t_tkn *)token_pos->content)->type == TKN_PIPE)
	{
		if (ft_stx_a_pipeline(token_pos->next) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

int ft_stx_a_simple_cmd(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (ft_stx_a_cmd_prefix(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_word(token_pos) == FT_SUCCESS)
		{
			if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
				return (FT_SUCCESS);
		}
	}
	if (ft_stx_a_cmd_prefix(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_word(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	if (ft_stx_a_cmd_prefix(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	if (ft_stx_a_word(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_cmd_suffix(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	}
	if (ft_stx_a_word(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	return (FT_ERROR);
}

int ft_stx_a_cmd_prefix(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	if (ft_stx_a_cmd_prefix(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

int ft_stx_a_cmd_suffix(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	if (ft_stx_a_cmd_suffix(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	if (ft_stx_a_word(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	if (ft_stx_a_cmd_suffix(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_word(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

int ft_stx_a_io_redir(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (ft_stx_a_redir(token_pos) == FT_SUCCESS)
		return (FT_SUCCESS);
	if (ft_stx_a_io_redir(token_pos) == FT_SUCCESS)
	{
		if (ft_stx_a_redir(token_pos) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

int ft_stx_a_redir(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (((t_tkn *)token_pos->content)->type == TKN_REDIRECT
		|| ((t_tkn *)token_pos->content)->type == TKN_FD_REDIRECT)
	{
		if (ft_stx_a_word(token_pos->next) == FT_SUCCESS)
			return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

int	ft_stx_a_word(t_list *token_pos)
{
	if (token_pos == 0)
		return (FT_ERROR);
	if (((t_tkn *)token_pos->content)->type == TKN_WORD)
	{
		return (FT_SUCCESS);
	}
	return (FT_ERROR);
}

// 위치를 갱신하는 지점****
// 이전 위치를 저장해둘 필요가 있는가? -> 재귀 중 백트래킹 되었을 때 최근에 본 위치를 기억해야하는가?
// 이중 포인터를 사용하지 않는 방식으로 구현하는 건 어떨끼?