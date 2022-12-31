/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2022/12/31 18:24:19 by kshim            ###   ########.fr       */
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
					&& ft_token_check_for_quote(token_node) == BOOL_TRUE)
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
	char	*tmp_buf;

	here_doc_fd = -1;
	tmp_buf = 0;
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
		if (is_env_expand == BOOL_TRUE)
		{
			ft_token_str_expansion(&buffer, dll_envp_tower->head, EXPAND_ENV_ONLY);
			// 확장을 한 경우에 '\n'가 붙지 않는다. 
				// !!!! 근데 이러면 '\n'이 붙어 있는데도 확장했다는 말 아닌가?
				// 뭔가 느낌이 이상하다.
			// 확장 안 한 경우에는 원래 문자열이 돌아와서 '\n' 이미 붙어있음.
				// 확장 수행 '여부'를 알 수 있으면 좋을까?
		}
		write(here_doc_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(here_doc_fd);
	return (FT_SUCCESS);
}


