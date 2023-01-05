/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 17:17:24 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	execute_cmd(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (is_built_in(token_tree->content))
		execute_builtin(token_tree->content, dll_envp_tower, m_pipe);
	else
		execute_external(token_tree, dll_envp_tower, m_pipe);
}

void	execute_fork(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	t_tree_node	*pipeline;
	pid_t		pid;
	int			status;
	int			iter;

	g_exit_code = 0;
	pipeline = token_tree; // 이거 굳이 해야함?
	iter = 0;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	// pipeline, m_pipe, iter, dll_envp_tower, pid
	
	// fork_before(pipeline, m_pipe, iter, dll_envp_tower);
	
	fork_routine(pipeline, m_pipe, &iter, dll_envp_tower);
	printf("after fork_routine iter === %d\n",iter);
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
	int	pid;

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
		pid = ft_fork();
		if (pid == 0)
			child_routine(m_pipe, pipeline, dll_envp_tower);// child routine   필요 인자     m_pipe, pipeline,dll_envp_tower 
		// 부모에서 close 실패한 경우, shell은 어떻게 동작하는게 맞을까?
			// close 함수 문서의 왜 실패했을 때 또 닫으면 안되는가? 참조
		else if (pid > 0)
			parent_routine(m_pipe);  //  &m_pipe로 가야 되나???
		else
		{
			parent_routine(m_pipe);  //
			break ;
			// 부모 동작 실행 후  break ;
		}
		pipeline = pipeline->right;
		(*iter)++;
	}
}

//  포인터로 가는거 맞는지 확인
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
	if (ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower,\
		m_pipe, &ft_execute_tree) == FT_ERROR)
	{
		// error 시 뒤처리
		exit(g_exit_code);
	}
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



int	is_built_in(t_tree_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd_name, "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "env"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "export"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "echo"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_tree_cmd *cmd, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (!ft_strcmp(cmd->cmd_name, "echo"))
		ft_echo(cmd, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "cd"))
		ft_cd(cmd, dll_envp_tower);
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		ft_pwd(m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "export"))
		ft_export(cmd, dll_envp_tower, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "unset"))
		ft_unset(cmd, dll_envp_tower);
	if (!ft_strcmp(cmd->cmd_name, "env"))
		ft_env(dll_envp_tower, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "exit"))
		ft_exit(cmd, m_pipe);
	return ;
}

void	execute_external(t_tree_node *node, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	char			*file_path;
	char			**env;

	file_path = set_file_path(((t_tree_cmd *)node->content)->cmd_name,
			dll_envp_tower);
	env = ft_set_char_envp_from_dll(dll_envp_tower, 0);
	ft_execve(file_path, ((t_tree_cmd *)node->content)->cmd_argv, env);
	if (!file_path)
		free(file_path);
}
