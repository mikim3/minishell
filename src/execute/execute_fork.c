/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/11 18:12:17 by kshim            ###   ########.fr       */
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
	m_pipe->stdfd[0] = dup(STDIN_FILENO);
	m_pipe->stdfd[1] = dup(STDOUT_FILENO);
	m_pipe->stdfd[2] = dup(STDERR_FILENO);
	fork_routine(pipeline, m_pipe, &exec_data, dll_envp_tower);
	fork_after_traversal(m_pipe);
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
		(m_pipe->pipe_num)++;
		(exec_data->iter)++;
	}
}
