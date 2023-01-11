/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:04:41 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 17:51:06 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	fork_action(t_tree_node *pipeline, \
	t_pipe *m_pipe, t_exec_fork *exec_data, t_detower *dll_envp_tower)
{
	exec_data->pid = ft_fork();
	if (exec_data->pid == 0)
		child_routine(m_pipe, pipeline, dll_envp_tower);
	else if (exec_data->pid > 0)
		parent_routine(m_pipe);
	else
	{
		parent_routine(m_pipe);
		return (FT_ERROR);
	}
	return (FT_SUCCESS);
}

void	parent_routine(t_pipe *m_pipe)
{
	set_signal(SIG_IGNORE, SIG_IGNORE);
	if (m_pipe->pre_pipe_check == BOOL_TRUE)
	{
		ft_close(m_pipe->pre_pipe_read_end);
		m_pipe->pre_pipe_check = BOOL_FALSE;
	}
	if (m_pipe->next_pipe_check == BOOL_TRUE)
	{
		ft_close(m_pipe->pipe[P_WRITE]);
		m_pipe->pre_pipe_check = BOOL_TRUE;
		m_pipe->pre_pipe_read_end = m_pipe->pipe[P_READ];
	}
	else
	{
		m_pipe->pre_pipe_check = BOOL_FALSE;
	}
}

void	child_routine(t_pipe *m_pipe, \
	t_tree_node *pipeline, t_detower *dll_envp_tower)
{
	set_signal(SIG_DEFAULT, SIG_DEFAULT);
	if (m_pipe->pre_pipe_check == BOOL_TRUE)
	{
		if (ft_dup2(m_pipe->pre_pipe_read_end, m_pipe->infile_fd) == -1
			|| ft_close(m_pipe->pre_pipe_read_end) == -1)
			exit(g_exit_code);
	}
	if (m_pipe->next_pipe_check == BOOL_TRUE)
	{
		if (ft_close(m_pipe->pipe[P_READ]) == -1
			|| ft_dup2(m_pipe->pipe[P_WRITE], m_pipe->outfile_fd) == -1
			|| ft_close(m_pipe->pipe[P_WRITE]) == -1)
			exit(g_exit_code);
	}
	if (ft_mnsh_tree_pre_traversal(pipeline->left, dll_envp_tower, \
		m_pipe, &ft_execute_tree) == FT_ERROR)
		exit(g_exit_code);
	exit(g_exit_code);
}

void	fork_after_traversal(t_pipe *m_pipe)
{
	dup2(m_pipe->stdfd[STDIN_FILENO], STDIN_FILENO);
	dup2(m_pipe->stdfd[STDOUT_FILENO], STDOUT_FILENO);
	dup2(m_pipe->stdfd[STDERR_FILENO], STDERR_FILENO);
	close(m_pipe->stdfd[STDIN_FILENO]);
	close(m_pipe->stdfd[STDOUT_FILENO]);
	close(m_pipe->stdfd[STDERR_FILENO]);
}
