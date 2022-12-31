/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2022/12/31 14:41:55 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_tokenizer.h"
#include "../../include/ft_doubly_linked_list.h"
#include "../../include/ft_token_expansion.h"



#include <stdio.h>

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	t_d_list	*envp_head;
	char		*redir;
	int			type;

	token_node = token_list;
	envp_head = dll_envp_tower->head;
	redir = ft_token_what_str(token_node);
	type = ft_token_what_type(token_node);
	printf("before_heredoc\n");
	while (type == TKN_NULL)
	{
		if (type == TKN_FD_REDIRECT)
		{
			while (ft_isdigit(*redir) == BOOL_FALSE)
				redir++;
		}
		if ((type == TKN_REDIRECT || type == TKN_FD_REDIRECT) && ft_strcmp(redir, "<<") == FT_SUCCESS)
		{
			printf("heredoc_checked\n");
			token_node = token_node->next;
			if (ft_token_is_expandable(token_node) == BOOL_TRUE)
			{
				if (ft_token_str_expansion((t_tkn *)token_node->content, envp_head, EXPAND_QUOTE_ONLY) == FT_ERROR)
					return (FT_ERROR);
				printf("heredoc_expanded - %s\n", ft_token_what_str(token_node));
				((t_tkn *)token_node->content)->expandable = BOOL_FALSE;
				
			}
		}
		token_node = token_node->next;
		type = ft_token_what_type(token_node);
	}
	return (FT_SUCCESS);
}
