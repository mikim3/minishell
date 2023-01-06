/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 13:31:22 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	execute_fork(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	t_tree_node	*pipeline;
	t_exec_fork	exec_data;

	exec_data.repeat = 0;
	g_exit_code = 0;
	pipeline = token_tree;
	exec_data.pid = 0;
	exec_data.iter = 0;
	exec_data.status = 0;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	fork_routine(pipeline, m_pipe, &exec_data, dll_envp_tower);
	while (exec_data.iter > 0)
	{
		wait_child(&exec_data);
		exec_data.iter--;
	}
	return ;
}

void	fork_routine(t_tree_node *pipeline, \
	t_pipe *m_pipe, t_exec_fork *exec_data, t_detower *dll_envp_tower)
{
	while (pipeline != 0)
	{
		if (next_pipe_check(pipeline, m_pipe) == FT_ERROR)
		{
			parent_routine(m_pipe);
			break ;
		}
		if ((exec_data->iter) == 0 && m_pipe->next_pipe_check == BOOL_FALSE
			&& is_built_in(pipeline->left->right->content) == BOOL_TRUE)
		{
			m_pipe->mnsh_builtin = BOOL_TRUE;
			if (ft_mnsh_tree_pre_traversal(pipeline->left, \
				dll_envp_tower, m_pipe, &ft_execute_tree) == FT_ERROR)
				return (fork_after_traversal(m_pipe));
			return (fork_after_traversal(m_pipe));
		}
		if (fork_action(\
			pipeline, m_pipe, exec_data, dll_envp_tower) == FT_ERROR)
			break ;
		pipeline = pipeline->right;
		(exec_data->iter)++;
	}
}

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

void	parent_routine(t_pipe	*m_pipe)
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
		m_pipe->pre_pipe_check = BOOL_FALSE;
}

void	child_routine(t_pipe *m_pipe, \
	t_tree_node *pipeline, t_detower *dll_envp_tower)
{
	set_signal(SIG_DEFAULT, SIG_DEFAULT);
	if (m_pipe->pre_pipe_check == BOOL_TRUE)
		if (ft_dup2(m_pipe->pre_pipe_read_end, m_pipe->infile_fd) == -1
			|| ft_close(m_pipe->pre_pipe_read_end) == -1)
			exit(g_exit_code);
	if (m_pipe->next_pipe_check == BOOL_TRUE)
		if (ft_close(m_pipe->pipe[P_READ]) == -1
			|| ft_dup2(m_pipe->pipe[P_WRITE], m_pipe->outfile_fd) == -1
			|| ft_close(m_pipe->pipe[P_WRITE]) == -1)
			exit(g_exit_code);
	if (ft_mnsh_tree_pre_traversal(pipeline->left, dll_envp_tower, \
		m_pipe, &ft_execute_tree) == FT_ERROR)// error 시 뒤처리 kshim -> 사실 자식은 닫아버리면 그게 뒤처리나 마찬가지긴하다.
		exit(g_exit_code);
	fork_after_traversal(m_pipe);
}

// traversal 후 처리 중 코드 중복이 있을 것 같아서 함수로 빼냈음. kshim 1/6
void	fork_after_traversal(t_pipe *m_pipe)
{
	if (m_pipe->mnsh_builtin == BOOL_FALSE)
		exit(g_exit_code);
	else
	{
		if (m_pipe->out_redirected == BOOL_TRUE)
			ft_close(m_pipe->outfile_fd);
		if (m_pipe->in_redirected == BOOL_TRUE)
			ft_close(m_pipe->infile_fd);
	}
}
