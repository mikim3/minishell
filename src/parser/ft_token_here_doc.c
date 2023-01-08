/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:53:23 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 08:17:00 by kshim            ###   ########.fr       */
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

int	ft_make_h_doc_loop(char *delimiter, \
	int here_doc_fd, t_detower *dll_envp_tower, int is_env_expand)
{
	char	*buffer;
	char	*tmp_buf;
	int		here_doc_stop;

	here_doc_stop = BOOL_FALSE;
	if (ft_make_h_doc_readline(&tmp_buf, &here_doc_stop) == FT_ERROR)
		return (FT_ERROR);
	if (here_doc_stop == BOOL_TRUE)
		return (free(tmp_buf), FT_SUCCESS);
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
	return (free(buffer), -1);
}

int	ft_make_h_doc_readline(char **buffer, int *here_doc_stop)
{
	int	org_exit_code;
	int	ret;
	int	tmp_fd;

	org_exit_code = g_exit_code;
	g_exit_code = 0;
	tmp_fd = dup(STDIN_FILENO);
	ret = FT_SUCCESS;
	*buffer = readline("> ");
	if (*buffer == 0)
	{
		if (g_exit_code == 0)
		{
			*here_doc_stop = BOOL_TRUE;
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[2C", STDOUT_FILENO);
			ret = FT_SUCCESS;
		}
		else if (g_exit_code == 1)
		{
			org_exit_code = 1;
			dup2(tmp_fd, STDIN_FILENO);
			close(tmp_fd);
			ret = FT_ERROR;
		}
	}
	g_exit_code = org_exit_code;
	return (ret);
}

// int	ft_make_h_doc_readline_eof_condition(int *here_doc_stop, int *org_exit_code, int tmp_fd)
// {
// 	if (g_exit_code == 0)
// 	{
// 		*here_doc_stop = BOOL_TRUE;
// 		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
// 		ft_putstr_fd("\033[2C", STDOUT_FILENO);
// 		return (FT_SUCCESS);
// 	}
// 	else if (g_exit_code == 1)
// 	{
// 		org_exit_code = 1;
// 		dup2(tmp_fd, STDIN_FILENO);
// 		close(tmp_fd);
// 		return(FT_ERROR);
// 	}
// }