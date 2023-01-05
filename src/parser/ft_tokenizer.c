/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:01:52 by kshim             #+#    #+#             */
/*   Updated: 2023/01/04 18:00:21 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	*ft_tokenizer(char *str)
{
	t_tknizer	tknizer;
	int			prev_type;
	int			error;
	prev_type = TKN_WORD;
	error = BOOL_FALSE;
	if (ft_initialize_tokenizer(&tknizer, str) == FT_ERROR)
		exit(1);
	while (*(tknizer.str_pos) != '\0')
	{
		error = ft_tokenizing_loop(&tknizer, error, &prev_type);
		if (error == BOOL_TRUE)
		{
			ft_free_tokenizer_list_and_token(&(tknizer.tkn_list), &(tknizer.tkn), TKN_TKNIZE_FAIL);
			exit(1);
		}
	}
	if (ft_token_processor(&tknizer, &prev_type) == FT_ERROR)
	{
		ft_free_tokenizer_list_and_token(&(tknizer.tkn_list), &(tknizer.tkn), TKN_TKNIZE_FAIL);
		exit(1);
	}
	return ((void *)(tknizer.tkn_list));
}

int	ft_initialize_tokenizer(t_tknizer *tknizer, char *str)
{
	tknizer->tkn_list = 0;
	tknizer->tkn = ft_new_token();
	if (tknizer->tkn == 0)
		return (FT_ERROR);
	tknizer->str_pos = str;
	tknizer->tkn_start = str;
	tknizer->tkn_len = 0;
	tknizer->oper_len = 0;
	tknizer->expandable = BOOL_FALSE;
	if (ft_isdigit(*str) == BOOL_TRUE)
		tknizer->io_num_mode = BOOL_TRUE;
	else
		tknizer->io_num_mode = BOOL_FALSE;
	return (FT_SUCCESS);
}

int	ft_tokenizing_loop(t_tknizer *tknizer, int error, int *prev_type)
{
	if (ft_is_quote(*(tknizer->str_pos)) == BOOL_TRUE)
		error = ft_close_quote(tknizer, prev_type);
	if (*(tknizer->str_pos) == '$')
		tknizer->expandable = BOOL_TRUE;
	if (error == BOOL_FALSE && *prev_type == TKN_OPERATOR)
	{
		if (tknizer->oper_len == 1
			|| ft_can_become_operator(*(tknizer->str_pos - 1),
				*(tknizer->str_pos), &(tknizer->oper_len)) == BOOL_FALSE)
			error = ft_token_processor(tknizer, prev_type);
	}
	if (error == BOOL_FALSE && *prev_type != TKN_OPERATOR
		&& ft_is_operator(*(tknizer->str_pos)) == BOOL_TRUE)
	{
		if (tknizer->io_num_mode == BOOL_TRUE)
			*prev_type = TKN_OPERATOR;
		else
			error = ft_token_processor(tknizer, prev_type);
	}
	if (error == BOOL_FALSE 
		&& ft_isspace(*(tknizer->str_pos)) == BOOL_TRUE)
	{
		if (tknizer->tkn_len != 0)
			error = ft_token_processor(tknizer, prev_type);
		tknizer->tkn_start++;
		tknizer->str_pos++;
		if (ft_isdigit(*(tknizer->str_pos)) == BOOL_TRUE)
			tknizer->io_num_mode = BOOL_TRUE;
	}
	else
	{
		if (*prev_type != TKN_OPERATOR
			&& ft_isdigit(*(tknizer->str_pos)) == BOOL_FALSE)
			tknizer->io_num_mode = BOOL_FALSE;
		tknizer->str_pos++;
		tknizer->tkn_len++;
	}
	return (error);
}

int	ft_close_quote(t_tknizer *tknizer, int *prev_type)
{
	char	target;
	
	if (*prev_type == TKN_OPERATOR
		&& ft_token_processor(tknizer, prev_type) == FT_ERROR)
		return (FT_ERROR);
	target = *(tknizer->str_pos);
	tknizer->tkn_len++;
	tknizer->str_pos++;
	while (*(tknizer->str_pos) != target)
	{
		if (*(tknizer->str_pos) == '\0')
			return (FT_ERROR);
		tknizer->tkn_len++;
		tknizer->str_pos++;
	}
	tknizer->io_num_mode = BOOL_FALSE;
	tknizer->expandable = BOOL_TRUE;
	*prev_type = TKN_WORD;
	return (FT_SUCCESS);
}
