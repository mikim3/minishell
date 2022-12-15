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

// 예외처리를 임시로 exit로 해둠. exit 사용을 위한 헤더
#include <stdlib.h>

void	*ft_tokenizer(char *str)
{
	t_tknizer	tknizer;
	int			prev_type;
	int			error;
	// 코드 밖 코멘트, 사용하지 않을 헤더 존재함
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
		error = ft_tokenizing_loop(&tknizer, &prev_type, error, &str);
		if (error == BOOL_TRUE)
			exit(1);
		str++;
	}
	if (ft_token_processor(&tknizer, str, &prev_type, TKN_NULL) == FT_ERROR)
		exit(1);
	return ((void *)(tknizer.tkn_list));
}

int	ft_tokenizing_loop(t_tknizer *tknizer, int *prev_type, int error, char **str)
{
	if (ft_is_quote(**str) == BOOL_TRUE)
		error = ft_close_quote(tknizer, str, prev_type);
	if (error == BOOL_FALSE && *prev_type == TKN_OPERATOR)
	{
		if (ft_can_become_operator(*(tknizer->tkn_start),
				**str, tknizer->tkn_len) == BOOL_FALSE)
			error = ft_token_processor(tknizer, *str, prev_type, TKN_WORD);
	}
	if (error == BOOL_FALSE
		&& *prev_type != TKN_OPERATOR && ft_is_operator(**str) == BOOL_TRUE)
		error = ft_token_processor(tknizer, *str, prev_type, TKN_OPERATOR);
	if (error == BOOL_FALSE && ft_isspace(**str) == BOOL_TRUE)
		error = ft_token_processor(tknizer, *str, prev_type, TKN_WORD);
	else
		tknizer->tkn_len++;
	return (error);
}

int	ft_close_quote(t_tknizer *tknizer, char **str, int *prev_type)
{
	char	target;
	// 형태 마음에 안든다. 최적화 가능할 것 같음.
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
	int		i;
	char	*type[5];

	i = 1;
	type[0] = "NULL";
	type[1] = "WORD";
	type[2] = "OPERATOR";
	type[3] = "PIPE";
	type[4] = "REDIRECT";
	while (token_list != 0)
	{
		printf("token %d : %s, ", i, ((t_tkn *)token_list->content)->str);
		printf("type %s\n", type[((t_tkn *)token_list->content)->type]);
		token_list = token_list->next;
		i++;
	}
	return ;
}
