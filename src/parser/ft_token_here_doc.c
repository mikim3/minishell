/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 08:22:55 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	char		*redir;
	int			type;

	token_node = token_list;
	type = ft_token_type(token_node);
	while (type != TKN_NULL)
	{
		if (type == TKN_REDIRECT || type == TKN_FD_REDIRECT)
		{
			redir = ft_token_str(token_node);
			if (type == TKN_FD_REDIRECT)
			{
				while (ft_isdigit(*redir) == BOOL_TRUE)
					redir++;
			}
			if (ft_check_here_doc(&token_node, redir, \
			token_list, dll_envp_tower) == FT_ERROR)
				return (FT_ERROR);
		}
		token_node = token_node->next;
		type = ft_token_type(token_node);
	}
	return (FT_SUCCESS);
}

int	ft_check_here_doc(t_list **token_node, char *redir, \
	t_list *token_list, t_detower *dll_envp_tower)
{
	char		**tkn_str_ptr;

	tkn_str_ptr = 0;
	if (ft_strcmp(redir, "<<") == FT_SUCCESS)
	{
		*token_node = (*token_node)->next;
		tkn_str_ptr = &(((t_tkn *)(*token_node)->content)->str);
		if (ft_here_doc_with_delimiter_control(
				token_node, token_list, dll_envp_tower) == FT_ERROR)
			return (FT_ERROR);
		((t_tkn *)(*token_node)->content)->expandable = BOOL_FALSE;
	}
	return (FT_SUCCESS);
}

int	ft_here_doc_with_delimiter_control(t_list **token_node, \
	t_list *token_list, t_detower *dll_envp_tower)
{
	char		**tkn_str_ptr;

	tkn_str_ptr = &(((t_tkn *)(*token_node)->content)->str);
	if (ft_token_is_expandable(*token_node) == BOOL_TRUE
		&& ft_token_check_for_quote(*token_node) == BOOL_TRUE)
	{
		if (ft_token_str_expansion(tkn_str_ptr, \
			dll_envp_tower->head, EXPAND_QUOTE_ONLY) == FT_ERROR
			|| ft_make_h_doc_wth_expand(*tkn_str_ptr, \
				dll_envp_tower, BOOL_FALSE) == FT_ERROR)
			return (ft_free_tokenizer_list_and_token(&token_list, \
				0, TKN_TKNIZE_SUCCESSED), FT_ERROR);
	}
	else
	{
		if (ft_make_h_doc_wth_expand(*tkn_str_ptr, \
			dll_envp_tower, BOOL_TRUE) == FT_ERROR)
			return (ft_free_tokenizer_list_and_token(&token_list, \
				0, TKN_TKNIZE_SUCCESSED), FT_ERROR);
	}
	return (FT_SUCCESS);
}
