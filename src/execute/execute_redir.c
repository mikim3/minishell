/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:01:23 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/11 17:38:04 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	execute_redir(t_tree_node *node, t_pipe *m_pipe)
{
	int		redir_fd;
	char	*redir;
	char	*file_name;

	redir_fd = -1;
	redir = ((t_tree_rdr *)node->content)->redir;
	file_name = ((t_tree_rdr *)node->content)->file_name;
	if (ft_isdigit(*redir) == BOOL_TRUE)
	{
		redir_fd = ft_atoi(redir);
		if (redir_fd < 0)
		{
			ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
			ft_putstr_fd(": file descriptor out of range", STDERR_FILENO);
			if (redir_fd == -1)
				redir_fd = -2;
		}
		while (ft_isdigit(*redir) == BOOL_TRUE)
			redir++;
	}
	if (ft_match_redir_symbol(redir, file_name, redir_fd, m_pipe) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_match_redir_symbol(\
	char *redir, char *file_name, int redir_fd, t_pipe *m_pipe)
{
	int	ret_val;

	ret_val = FT_SUCCESS;
	if (ft_strcmp(redir, "<") == FT_SUCCESS)
		ret_val = ft_redir_infile(file_name, m_pipe, redir_fd);
	else if (ft_strcmp(redir, ">") == FT_SUCCESS)
		ret_val = ft_redir_outfile(file_name, m_pipe, redir_fd);
	else if (ft_strcmp(redir, ">>") == FT_SUCCESS)
		ret_val = ft_redir_append(file_name, m_pipe, redir_fd);
	else if (m_pipe->here_doc_opened == BOOL_FALSE
		&& ft_strcmp(redir, "<<") == FT_SUCCESS)
		ret_val = ft_redir_here_doc(m_pipe, redir_fd);
	return (ret_val);
}

int	ft_redir_input_redirection(t_pipe *m_pipe, int file_fd, int redir_fd)
{
	if (redir_fd == -1)
	{
		if (ft_dup2(file_fd, m_pipe->infile_fd) == -1
			|| ft_close(file_fd) == -1)
			return (FT_ERROR);
	}
	else
	{
		if (ft_dup2(file_fd, redir_fd) == -1
			|| ft_close(file_fd) == -1)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}

int	ft_redir_output_redirection(t_pipe *m_pipe, int file_fd, int redir_fd)
{
	if (redir_fd == -1)
	{
		if (ft_dup2(file_fd, m_pipe->outfile_fd) == -1
			|| ft_close(file_fd) == -1)
			return (FT_ERROR);
	}
	else
	{
		if (ft_dup2(file_fd, redir_fd) == -1
			|| ft_close(file_fd) == -1)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
