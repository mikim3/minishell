/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/29 17:25:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	execute_fork(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	t_tree_node	*pipeline;
	pid_t		pid;
	int			status;
	int			iter;

	g_exit_code = 0;
	pipeline = token_tree;
	iter = 0;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	fork_routine(pipeline, m_pipe, &iter, dll_envp_tower);
	while (iter != 0)
	{
		wait_child();
		iter--;
	}
	return ;
}

void	fork_routine(t_tree_node *pipeline, \
	t_pipe *m_pipe, int *iter, t_detower *dll_envp_tower)
{
	while (pipeline != 0)
	{
		if (next_pipe_check(pipeline, m_pipe) == FT_ERROR)
			break ; // pipe 에러 시에 그 전 동작들은?
		if ((*iter) == 0 && m_pipe->next_pipe_check == BOOL_FALSE
			&& is_built_in(pipeline->left->right->content) == BOOL_TRUE)
		{
			m_pipe->mnsh_builtin = BOOL_TRUE;
			if (ft_tree_node_pre_traversal2(pipeline->left, \
				dll_envp_tower, m_pipe, &ft_execute_tree) == FT_ERROR)
			{
				///// 부모, non_pipe, 빌트인
			}
			return ;
		}
		if (fork_action(m_pipe, pipeline, dll_envp_tower) == FT_ERROR)
			break ;
		pipeline = pipeline->right;
		(*iter)++;
	}
}

int	fork_action(t_pipe *m_pipe, \
	t_tree_node *pipeline, t_detower *dll_envp_tower)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
		child_routine(m_pipe, pipeline, dll_envp_tower);
	else if (pid > 0)
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
	// printf("getpid() == %d \n", getpid());
	// printf("child_pid == %d \n", pid);	
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
	if (ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, \
		m_pipe, &ft_execute_tree) == FT_ERROR)// error 시 뒤처리
		exit(g_exit_code);
	if (m_pipe->mnsh_builtin == BOOL_FALSE)
		exit(g_exit_code);
	else
	{
		if (m_pipe->out_redirected == BOOL_TRUE)
			close(m_pipe->outfile_fd);
		if (m_pipe->in_redirected == BOOL_TRUE)
			close(m_pipe->infile_fd);
	}
}
