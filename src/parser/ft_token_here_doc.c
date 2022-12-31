/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2022/12/31 17:42:14 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_tokenizer.h"
#include "../../include/ft_doubly_linked_list.h"
#include "../../include/ft_token_expansion.h"

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	t_d_list	*envp_head;
	char		*redir;
	int			type;
	int			expanded;

	token_node = token_list;
	envp_head = dll_envp_tower->head;
	type = ft_token_what_type(token_node);
	expanded = BOOL_FALSE;
	while (type != TKN_NULL)
	{
		if (type == TKN_REDIRECT || type == TKN_FD_REDIRECT)
		{
			redir = ft_token_what_str(token_node);
			if (type == TKN_FD_REDIRECT)
			{
				while (ft_isdigit(*redir) == BOOL_TRUE)
					redir++;
			}
			if (ft_strcmp(redir, "<<") == FT_SUCCESS)
			{
				token_node = token_node->next;
				if (ft_token_is_expandable(token_node) == BOOL_TRUE
					|| ft_token_check_for_quote(token_node) == BOOL_TRUE)
				{
					if (ft_token_str_expansion(&(((t_tkn *)token_node->content)->str), envp_head, EXPAND_QUOTE_ONLY) == FT_ERROR)
						return (FT_ERROR);
					((t_tkn *)token_node->content)->expandable = BOOL_FALSE;
					ft_write_here_doc_with_expand_mode(ft_token_what_str(token_node), dll_envp_tower, BOOL_FALSE);
				}
				else
				{
					((t_tkn *)token_node->content)->expandable = BOOL_FALSE;
					ft_write_here_doc_with_expand_mode(ft_token_what_str(token_node), dll_envp_tower, BOOL_TRUE);
				}
			}	
		}
		token_node = token_node->next;
		type = ft_token_what_type(token_node);
	}
	return (FT_SUCCESS);
}

int	ft_write_here_doc_with_expand_mode(char *token_str, t_detower *dll_envp_tower, int is_env_expand)
{
	int		here_doc_fd;
	char	*buffer;
	char	*delimiter;

	here_doc_fd = -1;
	here_doc_fd = open(
				"/tmp/.mnsh_here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	delimiter = ft_strjoin(token_str, "\n");
	if (here_doc_fd == -1 || delimiter == 0)
		return (FT_ERROR);
	while (1)
	{
		buffer = get_next_line(0);
		if (buffer == 0)
			return (FT_ERROR);
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			free(delimiter);
			return (FT_ERROR);
		}
		// ft_token_str_expansion을 쓰려면 token 넣어야하도록 코드 짰음.
			// 이걸 string만 넣어도 동작할 수 있게 만드는게 좋을 것 같음.
		if (is_env_expand == BOOL_TRUE)
			ft_token_str_expansion(&buffer, dll_envp_tower->head, EXPAND_ENV_ONLY);
		write(here_doc_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(here_doc_fd);
	return (FT_SUCCESS);
}


