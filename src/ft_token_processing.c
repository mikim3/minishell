/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:49:46 by kshim             #+#    #+#             */
/*   Updated: 2022/12/16 10:38:42 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tokenizer.h"

int	ft_token_processor(
		t_tknizer *tknizer, int *prev_type, int tkn_type)
{
	if (tknizer->tkn_len != 0)
	{
		if (ft_token_set(tknizer, *prev_type) == FT_ERROR
			|| ft_token_cut(&(tknizer->tkn_list), tknizer->tkn) == FT_ERROR)
			return (FT_ERROR);
		tknizer->tkn = ft_new_token();
		if (tknizer->tkn == 0)
			return (FT_ERROR);
	}
	*prev_type = tkn_type;
	ft_token_start_set(tknizer);
	tknizer->tkn_len = 0;
	if (tkn_type == TKN_NULL)
	{
		tknizer->tkn->str = 0;
		tknizer->tkn->type = TKN_NULL;
		if (ft_token_cut(&(tknizer->tkn_list), tknizer->tkn) == FT_ERROR)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}

int	ft_token_set(t_tknizer *tknizer, int type)
{
	char	*new_str;

	new_str = ft_strndup(tknizer->tkn_start, tknizer->tkn_len);
	if (new_str == 0)
		return (FT_ERROR);
	tknizer->tkn->str = new_str;
	if (type == TKN_OPERATOR)
	{
		if (*(tknizer->tkn->str) == '|')
			tknizer->tkn->type = TKN_PIPE;
		else if (tknizer->io_num_mode == BOOL_TRUE)
			tknizer->tkn->type = TKN_IO_REDIRECT;
		else
			tknizer->tkn->type = TKN_REDIRECT;
	}
	else
		tknizer->tkn->type = type;
	return (FT_SUCCESS);
}

int	ft_token_cut(t_list **token_list, t_tkn *token)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node == 0)
		return (FT_ERROR);
	new_node->content = (void *)token;
	ft_lstadd_back(token_list, new_node);
	return (FT_SUCCESS);
}

t_tkn	*ft_new_token(void)
{
	t_tkn	*new_token;

	new_token = ft_calloc(1, sizeof(t_tkn));
	if (new_token == 0)
		return (0);
	return (new_token);
}

void	ft_token_start_set(t_tknizer *tknizer)
{
	while (ft_isspace(*(tknizer->str_pos)) == BOOL_TRUE)
	{
		tknizer->str_pos++;
	}
	tknizer->tkn_start = tknizer->str_pos;
	if (ft_isdigit(*(tknizer->str_pos)) == BOOL_TRUE)
		tknizer->io_num_mode = BOOL_TRUE;
	return ;
}
