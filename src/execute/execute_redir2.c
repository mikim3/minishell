/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:20:22 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 15:16:57 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_redir_infile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int			file_fd;

	if (ft_access(file_name, F_OK | R_OK) == -1)
		return (FT_ERROR);
	else
	{
		file_fd = ft_open(file_name, O_RDONLY, 0);
		if (file_fd == -1)
			return (FT_ERROR);
	}
	if (ft_redir_input_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_outfile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int			file_fd;

	file_fd = ft_open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (file_fd == -1)
		return (FT_ERROR);
	if (ft_redir_output_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_append(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int			file_fd;

	file_fd = ft_open(file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (file_fd == -1)
		return (FT_ERROR);
	if (ft_redir_output_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_here_doc(t_pipe *m_pipe, int redir_fd)
{
	int			file_fd;
	char		*tmp;

	tmp = ft_make_h_doc_file_name(m_pipe->pipe_num);
	if (tmp == 0)
		return (FT_ERROR);
	file_fd = ft_open(tmp, O_RDONLY, 0);
	if (file_fd == -1)
		return (free(tmp), FT_ERROR);
	m_pipe->here_doc_opened = BOOL_TRUE;
	if (unlink(tmp) < 0)
	{
		exitcode_with_err("unlink()", strerror(errno), 1);
		return (free(tmp), FT_ERROR);
	}
	free(tmp);
	if (ft_redir_input_redirection(m_pipe, file_fd, redir_fd) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
