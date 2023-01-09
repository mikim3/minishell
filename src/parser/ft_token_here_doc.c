/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 20:22:36 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower, \
	int *pipe_num)
{
	t_heredoc	heredoc;

	ft_memset(&heredoc, 0, sizeof(t_heredoc));
	heredoc.token_node = token_list;
	heredoc.type = ft_token_type(heredoc.token_node);
	while (heredoc.type != TKN_NULL)
	{
		if (heredoc.type == TKN_PIPE)
			(*pipe_num)++;
		if (heredoc.type == TKN_REDIRECT || heredoc.type == TKN_FD_REDIRECT)
		{
			heredoc.redir = ft_token_str(heredoc.token_node);
			if (heredoc.type == TKN_FD_REDIRECT)
			{
				while (ft_isdigit(*heredoc.redir) == BOOL_TRUE)
					heredoc.redir++;
			}
			if (ft_check_here_doc(\
				&heredoc, dll_envp_tower, *pipe_num) == FT_ERROR)
				return (FT_ERROR);
		}
		heredoc.token_node = (heredoc.token_node)->next;
		heredoc.type = ft_token_type(heredoc.token_node);
	}
	return (FT_SUCCESS);
}

int	ft_check_here_doc(t_heredoc *heredoc, \
	t_detower *dll_envp_tower, int pipe_num)
{
	char		**tkn_str_ptr;

	tkn_str_ptr = 0;
	if (ft_strcmp(heredoc->redir, "<<") == FT_SUCCESS)
	{
		heredoc->token_node = (heredoc->token_node)->next;
		tkn_str_ptr = &(((t_tkn *)(heredoc->token_node)->content)->str);
		if (ft_here_doc_with_delimiter_control(
				&(heredoc->token_node), heredoc->token_list, \
				dll_envp_tower, pipe_num) == FT_ERROR)
			return (FT_ERROR);
		((t_tkn *)(heredoc->token_node)->content)->expandable = BOOL_FALSE;
	}
	return (FT_SUCCESS);
}

int	ft_here_doc_with_delimiter_control(t_list **token_node, \
	t_list *token_list, t_detower *dll_envp_tower, int pipe_num)
{
	char		**tkn_str_ptr;

	tkn_str_ptr = &(((t_tkn *)(*token_node)->content)->str);
	if (ft_token_is_expandable(*token_node) == BOOL_TRUE
		&& ft_token_check_for_quote(*token_node) == BOOL_TRUE)
	{
		if (ft_token_str_expansion(tkn_str_ptr, \
			dll_envp_tower->head, EXPAND_QUOTE_ONLY) == FT_ERROR
			|| ft_make_h_doc_wth_expand(*tkn_str_ptr, \
				dll_envp_tower, pipe_num, \
					BOOL_FALSE) == FT_ERROR)
			return (ft_free_tokenizer_list_and_token(&token_list, \
				0, TKN_TKNIZE_SUCCESSED), FT_ERROR);
	}
	else
	{
		if (ft_make_h_doc_wth_expand(*tkn_str_ptr, \
			dll_envp_tower, pipe_num, \
				BOOL_TRUE) == FT_ERROR)
			return (ft_free_tokenizer_list_and_token(&token_list, \
				0, TKN_TKNIZE_SUCCESSED), FT_ERROR);
	}
	return (FT_SUCCESS);
}

int	ft_make_h_doc_wth_expand(\
	char *token_str, t_detower *dll_envp_tower, \
	int pipe_num, int is_env_expand)
{
	int		here_doc_fd;
	char	*delimiter;
	int		ret;

	if (ft_make_h_doc_set_before_loop(token_str, &delimiter, \
		&here_doc_fd, pipe_num) == FT_ERROR)
		return (FT_ERROR);
	set_signal(SIG_HERE_DOC, SIG_IGNORE);
	while (1)
	{
		ret = ft_make_h_doc_loop(\
			delimiter, here_doc_fd, dll_envp_tower, is_env_expand);
		if (ret == FT_ERROR || ret == FT_SUCCESS)
			break ;
	}
	ft_close(here_doc_fd);
	return (set_signal(SIG_HANDLER, SIG_IGNORE), free(delimiter), ret);
}

int	ft_make_h_doc_set_before_loop(char *token_str, char **delimiter, \
	int *here_doc_fd, int pipe_num)
{
	char	*f_name;

	*here_doc_fd = -1;
	f_name = ft_make_h_doc_file_name(pipe_num);
	if (f_name == 0)
		return (FT_ERROR);
	*here_doc_fd = ft_open(f_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(f_name);
	if (*here_doc_fd == -1)
		return (FT_ERROR);
	*delimiter = ft_strjoin(token_str, "\n");
	if (*delimiter == 0)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
