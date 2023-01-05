/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:01:23 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 12:57:36 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"
#include <fcntl.h>

#include "../../include/ft_wrapper_functions.h"

// redirection에 실패하는 케이스 존재할 수 있음
// redir_fd 할 때 대상 fd가 available한지 확인하는 부분 넣으면 좋을 것 같음

int	execute_redir(t_tree_node *node, t_pipe *m_pipe)
{
	int		redir_fd;
	char	*redir;
	char	*file_name;
	int		ret_val;

	redir_fd = -1;
	redir = ((t_tree_redir *)node->content)->redir;
	file_name = ((t_tree_redir *)node->content)->file_name;
	if (ft_isdigit(*redir) == BOOL_TRUE)
	{
		redir_fd = ft_atoi(redir);
		if (redir_fd < 0)
			return (FT_ERROR);
		while (ft_isdigit(*redir) == BOOL_TRUE)
			redir++;
	}
	if (ft_strcmp(redir, "<") == FT_SUCCESS)
		ret_val = ft_redir_infile(file_name, m_pipe, redir_fd);
	else if (ft_strcmp(redir, ">") == FT_SUCCESS)
		ret_val = ft_redir_outfile(file_name, m_pipe, redir_fd);
	else if (ft_strcmp(redir, ">>") == FT_SUCCESS)
		ret_val = ft_redir_append(file_name, m_pipe, redir_fd);
	else if (ft_strcmp(redir, "<<") == FT_SUCCESS)
		ret_val = ft_redir_here_doc(m_pipe, redir_fd);
	if (ret_val == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_infile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	struct stat buf;

	if (redir_fd != -1 && ft_fstat(redir_fd, &buf) == -1)
		return (FT_ERROR);
	if (ft_access(file_name, F_OK | R_OK) == FT_ERROR)
		return (FT_ERROR);
	else
	{
		file_fd= ft_open(file_name, O_RDWR, 0);
		if (file_fd== -1)
			return (FT_ERROR);
	}
	if (ft_redir_input_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_outfile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	struct stat buf;

	if (redir_fd != -1 && ft_fstat(redir_fd, &buf) == -1)
		return (FT_ERROR);
	file_fd= ft_open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (file_fd== -1)
		return (FT_ERROR);
	if (ft_redir_output_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_append(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	struct stat buf;

	if (redir_fd != -1 && ft_fstat(redir_fd, &buf) == -1)
		return (FT_ERROR);
	file_fd= ft_open(file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (file_fd== -1)
		return (FT_ERROR);
	if (ft_redir_output_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_here_doc(t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	struct stat buf;

	if (redir_fd != -1 && ft_fstat(redir_fd, &buf) == -1)
		return (FT_ERROR);
	file_fd = ft_open("/tmp/.mnsh_here_doc.tmp", O_RDONLY, 0);
	if (file_fd== -1)
		return (FT_ERROR);
	if (unlink("/tmp/.mnsh_here_doc.tmp") < 0)
	{
		exitcode_with_err("unlink()", strerror(errno), 1);
		return (FT_ERROR);
	}
	if (ft_redir_input_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_input_redirection(t_pipe *m_pipe, int file_fd, int redir_fd)
{
	if (redir_fd == -1)
	{
		if (m_pipe->mnsh_builtin == BOOL_TRUE)
		{
			if (m_pipe->in_redirected == BOOL_TRUE)
			{
				if (ft_close(m_pipe->infile_fd) == -1)
					return (FT_ERROR);
			}
			m_pipe->infile_fd = file_fd;
		}
		else
		{
			if (ft_dup2(file_fd, m_pipe->infile_fd) == -1
				|| ft_close(file_fd) == -1)
				return (FT_ERROR);
		}
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
		if (m_pipe->mnsh_builtin == BOOL_TRUE)
		{
			if (m_pipe->out_redirected == BOOL_TRUE)
			{
				if (ft_close(m_pipe->outfile_fd) == -1)
					return (FT_ERROR);
			}
			m_pipe->outfile_fd = file_fd;
		}
		else
		{
			if (ft_dup2(file_fd, m_pipe->outfile_fd) == -1
				|| ft_close(file_fd) == -1)
				return (FT_ERROR);
		}
	}
	else
	{
		if (ft_dup2(file_fd, redir_fd) == -1
			|| ft_close(file_fd) == -1)
			return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
