/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:49:46 by kshim             #+#    #+#             */
/*   Updated: 2022/12/15 15:11:27 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tokenizer.h"

int	ft_token_processor(
		t_tknizer *tknizer, char *str, int *prev_type, int tkn_type)
{
	if (tknizer->tkn_len != 0)
	{
		if (ft_token_set(tknizer->tkn, tknizer->tkn_start,
				tknizer->tkn_len, *prev_type) == FT_ERROR
			|| ft_token_cut(&(tknizer->tkn_list), tknizer->tkn) == FT_ERROR)
			return (FT_ERROR);
		tknizer->tkn = ft_new_token();
		if (tknizer->tkn == 0)
			return (FT_ERROR);
	}
	*prev_type = tkn_type;
	tknizer->tkn_len = 0;
	ft_token_start_set(tknizer, str);
	if (tkn_type == TKN_NULL)
	{
		tknizer->tkn->str = 0;
		tknizer->tkn->type = tkn_type;
		if (ft_token_cut(&(tknizer->tkn_list), tknizer->tkn) == FT_ERROR)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}

int	ft_token_set(t_tkn *token, char *tkn_start, int token_len, int type)
{
	char	*new_str;

	new_str = ft_strndup(tkn_start, token_len);
	if (new_str == 0)
		return (FT_ERROR);
	token->str = new_str;
	if (type == TKN_OPERATOR)
	{
		if (*(token->str) == '|')
			token->type = TKN_PIPE;
		else
			token->type = TKN_REDIRECT;
	}
	else
		token->type = type;
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

void	ft_token_start_set(t_tknizer *tknizer, char *str)
{
	while (ft_isspace(*str) == BOOL_TRUE)
	{
		str++;
	}
	tknizer->tkn_start = str;
	return ;
}
