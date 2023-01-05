/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 15:31:05 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	t_d_list	*envp_head;
	char		*redir;
	int			type;
	char		**tkn_str_ptr;

	token_node = token_list;
	envp_head = dll_envp_tower->head;
	type = ft_token_type(token_node);
	tkn_str_ptr = 0;
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
			if (ft_strcmp(redir, "<<") == FT_SUCCESS)
			{
				token_node = token_node->next;
				tkn_str_ptr = &(((t_tkn *)token_node->content)->str);
				if (ft_token_is_expandable(token_node) == BOOL_TRUE
					&& ft_token_check_for_quote(token_node) == BOOL_TRUE)
				{
					if (ft_token_str_expansion(tkn_str_ptr, \
						envp_head, EXPAND_QUOTE_ONLY) == FT_ERROR
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
				((t_tkn *)token_node->content)->expandable = BOOL_FALSE;
			}
		}
		token_node = token_node->next;
		type = ft_token_type(token_node);
	}
	return (FT_SUCCESS);
}

// int ft_here_doc_loop()
// {
	
// }

// 반복문 내에서 실패 시 break 시키고 while 바깥에서 예외 처리하는 건?
int	ft_make_h_doc_wth_expand(char *token_str, t_detower *dll_envp_tower, int is_env_expand)
{
	int		here_doc_fd;
	char	*buffer;
	char	*delimiter;
	char	*tmp_buf;

	here_doc_fd = -1;
	tmp_buf = 0;
	buffer = 0;
	here_doc_fd = ft_open(
			"/tmp/.mnsh_here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (here_doc_fd == -1)
		return (FT_ERROR);
	delimiter = ft_strjoin(token_str, "\n");
	if (delimiter == 0)
		return (FT_ERROR);
	while (1)
	{
		tmp_buf = readline("> ");
		if (tmp_buf == 0)
			return (free(delimiter), FT_ERROR);
		buffer = ft_strjoin(tmp_buf, "\n");
		free(tmp_buf);
		tmp_buf = 0;
		if (buffer == 0)
			return (free(delimiter), FT_ERROR);
		if (ft_strcmp(buffer, delimiter) == 0)
			return (ft_free_here_doc_memory(delimiter, buffer), FT_SUCCESS);
		if (is_env_expand == BOOL_TRUE)
		{
			if (ft_token_str_expansion(&buffer, \
				dll_envp_tower->head, EXPAND_ENV_ONLY) == FT_ERROR)
				return (ft_free_here_doc_memory(delimiter, buffer), FT_ERROR);
		}
		if (write(here_doc_fd, buffer, ft_strlen(buffer)) < 0)
			return (ft_free_here_doc_memory(delimiter, buffer), FT_ERROR);
		free(buffer);
		buffer = 0;
	}
	ft_close(here_doc_fd);
	return (FT_SUCCESS);
}

void	ft_free_here_doc_memory(char *delimiter, char *buffer)
{
	free(buffer);
	free(delimiter);
	return ;
}
