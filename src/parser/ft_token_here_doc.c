/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 16:10:31 by kshim            ###   ########.fr       */
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

int	ft_make_h_doc_wth_expand(\
	char *token_str, t_detower *dll_envp_tower, int is_env_expand)
{
	int		here_doc_fd;
	char	*delimiter;
	int		ret;

	here_doc_fd = -1;
	here_doc_fd = ft_open(
			"/tmp/.mnsh_here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (here_doc_fd == -1)
		return (FT_ERROR);
	delimiter = ft_strjoin(token_str, "\n");
	if (delimiter == 0)
		return (FT_ERROR);
	while (1)
	{
		ret = ft_make_h_doc_loop(\
			delimiter, here_doc_fd, dll_envp_tower, is_env_expand);
		if (ret == FT_ERROR)
			break ;
		else if (ret == FT_SUCCESS)
			return (free(delimiter), FT_SUCCESS);
	}
	free(delimiter);
	ft_close(here_doc_fd);
	return (FT_ERROR);
}

int	ft_make_h_doc_loop(char *delimiter, \
	int here_doc_fd, t_detower *dll_envp_tower, int is_env_expand)
{
	char	*buffer;
	char	*tmp_buf;

	tmp_buf = readline("> ");
	if (tmp_buf == 0)
		return (FT_ERROR);
	buffer = ft_strjoin(tmp_buf, "\n");
	free(tmp_buf);
	if (buffer == 0)
		return (FT_ERROR);
	if (ft_strcmp(buffer, delimiter) == 0)
		return (free(buffer), FT_SUCCESS);
	if (is_env_expand == BOOL_TRUE)
	{
		if (ft_token_str_expansion(&buffer, \
			dll_envp_tower->head, EXPAND_ENV_ONLY) == FT_ERROR)
			return (free(buffer), FT_ERROR);
	}
	if (write(here_doc_fd, buffer, ft_strlen(buffer)) < 0)
		return (free(buffer), FT_ERROR);
	free(buffer);
	buffer = 0;
	return (-1);
}
