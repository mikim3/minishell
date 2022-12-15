/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:01:52 by kshim             #+#    #+#             */
/*   Updated: 2022/12/13 12:33:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "../include/ft_tokenizer.h"

// readline으로 반환된 문자열을 word, operator(pipe, redirect) 단위로 끊어서 저장하는 부분

// Shell Command language 문서의 Token Recognition 절차를 그대로 조건화했다.
// 조건을 조정하거나 함수로 빼낼 수 있을 것 같음.

// 조건문 자체도 더 축약 가능할 것 같다.
	// 지금 방식은 cmd 문자열의 각 단어 단위로 작업을 진행한다.
		// 이렇게하면 각 단어마다 할당 해제 계속 함.
	// 그렇다면 새롭게 추가할 예정인 단어 범위를 진행하다가 추가 타이밍이 되면 단어를 더하게 만드는 건 어떨까?

#include <stdlib.h>

void	*ft_tokenizer(char *str)
{
	t_tknizer	tknizer;
	int			prev_type;
	int			error;

	prev_type = TKN_NULL;
	error = BOOL_FALSE;
	tknizer.tkn_start = str;
	tknizer.tkn_len = 0;
	tknizer.tkn_list = 0;
	tknizer.tkn = ft_new_token();
	if (tknizer.tkn == 0)
		return (0);
	while (*str != '\0')
	{
		if (ft_is_quote(*str) == BOOL_TRUE)
			error = ft_close_quote(&tknizer, &str, &prev_type);
		if (error == BOOL_FALSE && prev_type == TKN_OPERATOR)
		{
			if (ft_can_become_operator(
					*(tknizer.tkn_start), *str, tknizer.tkn_len) == BOOL_FALSE)
				error = ft_token_processor(&tknizer, str, &prev_type, TKN_WORD);
		}
		if (error == BOOL_FALSE
			&& prev_type != TKN_OPERATOR && ft_is_operator(*str) == BOOL_TRUE)
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_OPERATOR);
		if (error == BOOL_FALSE && ft_isspace(*str) == BOOL_TRUE)
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_WORD);
		else
			tknizer.tkn_len++;
		str++;
		if (error == BOOL_FALSE && *str == '\0')
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_NULL);
		if (error == BOOL_TRUE)
			exit(1);
	}
	return ((void *)(tknizer.tkn_list));
}

int	ft_is_quote(char cha)
{
	if (cha == '\'' || cha == '\"')
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

int	ft_close_quote(t_tknizer *tknizer, char **str, int *prev_type)
{
	char	target;

	target = **str;
	tknizer->tkn_len++;
	(*str)++;
	while (**str != target)
	{
		if (**str == '\0')
			return (FT_ERROR);
		tknizer->tkn_len++;
		(*str)++;
	}
	if (**str == '\0')
		return (FT_ERROR);
	tknizer->tkn_len++;
	(*str)++;
	*prev_type = TKN_WORD;
	return (FT_SUCCESS);
}

int	main(void)
{
	t_list		*token_list;
	char		*input;
//	t_tree_node	*token_tree;

	while (1)
	{
		input = readline("minishell$ ");
		token_list = (t_list *)ft_tokenizer(input);
		test_print_token_lst(token_list);
	}

	return (0);
}

void	test_print_token_lst(t_list *token_list)
{
	int	i;

	i = 1;
	while (token_list != 0)
	{
		printf("token %d : %s\n", i, ((t_tkn *)token_list->content)->str);
		token_list = token_list->next;
		i++;
	}
	return ;
}
