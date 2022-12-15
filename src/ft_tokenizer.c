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

#include "../include/ft_tokenizer.h"

// readline으로 반환된 문자열을 word, operator(pipe, redirect) 단위로 끊어서 저장하는 부분

// Shell Command language 문서의 Token Recognition 절차를 그대로 조건화했다.
// 조건을 조정하거나 함수로 빼낼 수 있을 것 같음.

// 조건문 자체도 더 축약 가능할 것 같다.
	// 지금 방식은 cmd 문자열의 각 단어 단위로 작업을 진행한다.
		// 이렇게하면 각 단어마다 할당 해제 계속 함.
	// 그렇다면 새롭게 추가할 예정인 단어 범위를 진행하다가 추가 타이밍이 되면 단어를 더하게 만드는 건 어떨까?

#include <stdio.h>
#include <stdlib.h>

void	*ft_tokenizer(char *str)
{
	t_tknizer	tknizer;
	int			prev_type;
	int			error;

	prev_type = TKN_TYPE_NULL;
	error = BOOL_FALSE;
	tknizer.tkn_start = str;
	tknizer.tkn_len = 0;
	tknizer.tkn_list = 0;
	tknizer.tkn = ft_new_token();
	if (tknizer.tkn == 0)
		return (0);
	while (*str != '\0')
	{
		/*
		if (ft_is_quote(*str) == BOOL_TRUE)
		{
			if (ft_close_quote(tkn_start, &token_len) = FT_ERROR)
				return (ft_free_tokenizer(), FT_ERROR);
		}
		*/
		if (error == BOOL_FALSE && prev_type == TKN_TYPE_OPERATOR)
		{
			if (ft_can_become_operator(
					*(tknizer.tkn_start), *str, tknizer.tkn_len) == BOOL_FALSE)
				error = ft_token_processor(&tknizer, str, &prev_type, TKN_TYPE_WORD);
		}
		if (error == BOOL_FALSE && prev_type != TKN_TYPE_OPERATOR && ft_is_operator(*str) == BOOL_TRUE)
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_TYPE_OPERATOR);
		if (error == BOOL_FALSE && ft_isspace(*str) == BOOL_TRUE)
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_TYPE_WORD);
		else
			tknizer.tkn_len++;
		str++;
		if (error == BOOL_FALSE && *str == '\0')
			error = ft_token_processor(&tknizer, str, &prev_type, TKN_TYPE_NULL);
		if (error == BOOL_TRUE)
			exit(1);
	}
	return ((void *)(tknizer.tkn_list));
}

int	ft_token_processor(
		t_tknizer *tknizer, char *str, int *prev_type, int tkn_type)
{
	if (tknizer->tkn_len != 0)
	{
		if (ft_token_set(
				tknizer->tkn, tknizer->tkn_start, tknizer->tkn_len) == FT_ERROR)
			return (FT_ERROR);
		tknizer->tkn = ft_token_cut(&(tknizer->tkn_list), tknizer->tkn);
		if (tknizer->tkn == 0)
			return (FT_ERROR);
	}
	tknizer->tkn_len = 0;
	ft_token_start_set(tknizer, str);
	*prev_type = tkn_type;
	if (tkn_type == TKN_TYPE_NULL)
		free(tknizer->tkn);
	return (FT_SUCCESS);
}

int	ft_token_set(t_tkn *token, char *tkn_start, int token_len)
{
	char	*new_str;

	new_str = ft_strndup(tkn_start, token_len);
	if (new_str == 0)
		return (FT_ERROR);
	token->str = new_str;
	return (FT_SUCCESS);
}

t_tkn	*ft_token_cut(t_list **token_list, t_tkn *token)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node == 0)
		return (0);
	new_node->content = (void *)token;
	ft_lstadd_back(token_list, new_node);
	return (ft_new_token());
}

t_tkn	*ft_new_token(void)
{
	t_tkn	*new_token;

	new_token = ft_calloc(1, sizeof(t_tkn));
	if (new_token == 0)
		return (0);
	return (new_token);
}

void	ft_token_start_set(t_tknizer *tknizer, char *str)
{
	while (ft_isspace(*str) == BOOL_TRUE)
	{
		str++;
	}
	tknizer->tkn_start = str;
	return ;
}

int ft_can_become_operator(char diff_target, char cha, int token_len)
{
	if (token_len > 1)
		return (BOOL_FALSE);
	if (diff_target == cha)
		return (BOOL_TRUE);
	return (BOOL_FALSE);
	// |는 어떻게 처리하지?
}

int	ft_is_operator(char cha)
{
	if (cha == '<' || cha == '>' || cha == '|')
		return (BOOL_TRUE);
	return (BOOL_FALSE);
}

/*
int	ft_is_quote()
{

}

int	ft_close_quote()
{

}
*/

int		main(int argc, char **argv)
{
//	t_tree_node	*token_tree;
	t_list		*token_list;
	char		*input;
	// 테스트용 -> argv 한 묶음으로만 받기
	if (argc >= 3)
		return (1);
	input = argv[1];
	token_list = (t_list *)ft_tokenizer(input);
	test_print_token_lst(token_list);
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