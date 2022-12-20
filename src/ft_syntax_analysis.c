/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:41:04 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 13:46:57 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tokenizer.h"
// #include "../include/ft_tree.h"

#include <stdio.h>

int	ft_syntax_analysis(t_list *token_list)
{
	if (((t_tkn *)token_list->content)->type == TKN_NULL)
		return (FT_SUCCESS);
	if (ft_stx_a_pipeline(token_list, token_list, 1) == -1)
	{
		printf("\nsyntax error\n\n");
		return (FT_ERROR);
	}
	printf("\nsyntax appropriate\n\n");
	return (FT_SUCCESS);
}

// 재귀 함수
int	ft_stx_a_pipeline(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return(-1);
	if (((t_tkn *)token->content)->type == TKN_PIPE)
		return (-1);
	token_pos = ft_stx_a_simple_cmd(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	token = ft_lst_num(token_list, token_pos);
	if (((t_tkn *)token->content)->type == TKN_NULL)
		return (token_pos);
	if (((t_tkn *)token->content)->type == TKN_PIPE)
	{
		token_pos = ft_stx_a_pipeline(token_list, token->next, token_pos + 1);
		if (token_pos == -1)
			return (-1);
	}
	else
	{
		// pipe 안오는데 null 아니면 실패 아닌가?
		return (-1);
	}
	return (token_pos);
}

// lst 순회해서 위치 찾는 부분 최적화할 수 없을까?

// 이 함수는 5가지 케이스를 모두 테스트해야 함. (재귀 함수 아님)
	// 이 함수 내에서의 위치를 온존
	// 2분기 존재
		// 조건1-1 cmd_prefix == true인 경우
			// 조건1-2 cmd == true인 경우
				// 조건1-3 cmd_suffix == true인 경우
		// 만족한 만큼만 적용한 위치(token_pos) 반환

		// cmd_prefix == false인 경우에만 진입 : 조건2
		// 조건2-1 cmd == true인 경우
			// 조건2-2 cmd_suffix == true인 경우
		// 역시나 만족한 만큼만 반환
		// 모두 실패할 경우 '-1'
	// 반환 받은 결과가 -1이 아니라면 다음 '단계'로
	// 반환 받은 결고라ㅏ -1이라면 다음 '조건'으로
	// 마지막 조건도 오류라면 '-1' 반환
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
		// cmd_prefix 뒤에 cmd 못올 경우 동작이 이런 식이 맞나?
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
	// 조건문 빠져 나오는 경우가 존재할 수 있나?
	// 만약 존재할 경우에는 무엇을 반환해야하는가?
	stack_pos = token_pos;
	return (stack_pos);
}

// 이하 함수는 재귀 함수이거나, 재귀의 끝을 나타내는 함수임
int ft_stx_a_cmd_prefix(t_list *token_list, t_list *token, int token_pos)
{
	// 우선 현재 token과 그 뒤가 redir인지 확인한다.
	token_pos = ft_stx_a_redir(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	// prefix로 재귀할 때, 현재 token의 앞을 보는가 뒤를 보는가?
		// tree에 저장할 순서를 생각하면 될 것 같은데?
		// 근데 tree 저장 알고리즘 바꾸면 그만이니 그냥 뒤 보게하는게 편한거 아닌가?
			// 현재까지 읽은 위치도 반환할 수 있으니.
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (((t_tkn *)token->content)->type == TKN_NULL)
		return (token_pos);
	// 재귀했을 때 -1 반환되는 경우와 token_pos 반환되는 경우의 차이.
	if (((t_tkn *)token->content)->type != TKN_WORD)
	{
		token_pos = ft_stx_a_cmd_prefix(token_list, token, token_pos);
		if (token_pos == -1)
			return (-1);
	}
	return (token_pos);
}

// suffix의 경우 WORD가 섞인 조합도 재귀적으로 검증할 수 있는 형태가 필요하다.
int ft_stx_a_cmd_suffix(t_list *token_list, t_list *token, int token_pos)
{
	// 우선 현재 token이 null인지 보고, null이 아니라면 그 token이 redir 혹은 word인지 확인한다.
	if (((t_tkn *)token->content)->type == TKN_NULL)
		return (token_pos);
	else if (((t_tkn *)token->content)->type == TKN_WORD)
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
	if (((t_tkn *)token->content)->type == TKN_NULL)
		return (token_pos);
	if (((t_tkn *)token->content)->type == TKN_PIPE)
		return (token_pos);
	// 재귀했을 때 -1 반환되는 경우와 token_pos 반환되는 경우의 차이.
	token_pos = ft_stx_a_cmd_suffix(token_list, token, token_pos);
	if (token_pos == -1)
		return (-1);
	// suffix는 언제 끝날까?
	return (token_pos);
}

int ft_stx_a_redir(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (((t_tkn *)token->content)->type == TKN_REDIRECT
		|| ((t_tkn *)token->content)->type == TKN_FD_REDIRECT)
	{
		token_pos = ft_stx_a_word(token_list, token->next, token_pos + 1);
		if (token_pos == -1)
			return (-1);
	}
	else
		return (-1);
	return (token_pos);
}

// redir도 word로 들어옴 -> word에서 다음에 읽을 위치를 지정하면 됨. return (token_pos++);
int	ft_stx_a_word(t_list *token_list, t_list *token, int token_pos)
{
	token = ft_lst_num(token_list, token_pos);
	if (token == 0)
		return (-1);
	if (((t_tkn *)token->content)->type == TKN_NULL)
		return (-1);
	if (((t_tkn *)token->content)->type != TKN_WORD)
		return (-1);
	return (token_pos + 1);
}

// 위치를 갱신하는 지점****
// 이전 위치를 저장해둘 필요가 있는가? -> 재귀 중 백트래킹 되었을 때 최근에 본 위치를 기억해야하는가?
// 이중 포인터를 사용하지 않는 방식으로 구현하는 건 어떨끼?