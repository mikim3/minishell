/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 17:15:36 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

#include "../../include/ft_wrapper_functions.h"

void execute_cmd(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (is_built_in(token_tree->content))
		execute_builtin(token_tree->content, dll_envp_tower, m_pipe);
	else
		execute_external(token_tree, dll_envp_tower, m_pipe);
}

void	execute_fork(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	t_tree_node *pipeline;
	pid_t		pid;
	pid_t		w_pid;
	int			status;
	int			iter;

	g_exit_code = 0;
	pipeline = token_tree;
	iter = 0;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	while (pipeline != 0)
	{
		if (next_pipe_check(pipeline, m_pipe) == FT_ERROR)
			break ; // pipe 에러 시에 그 전 동작들은?
		if (iter == 0 && m_pipe->next_pipe_check == BOOL_FALSE
			&& is_built_in(pipeline->left->right->content) == BOOL_TRUE)
		{
			m_pipe->mnsh_builtin = BOOL_TRUE;
			if (ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, m_pipe, &ft_execute_tree) == FT_ERROR)
			{
				///// 부모, non_pipe, 빌트인
			}
			return ;
		}
		pid = ft_fork();
		if (pid == 0)
		{	
			ft_putstr_fd("set_sig SIGHANDLER 자식\n",STDERR_FILENO);
			set_signal(SIG_DEFAULT, SIG_DEFAULT); //이게 없으면 SIG_QUIT가 IGN상태이지만  그렇다고 이게 있다고 SIG_CHILD_HANDLER대로 작동하지는 않음 뭘까?
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
			if (ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, m_pipe, &ft_execute_tree) == FT_ERROR)
			{
				
			}
			if (m_pipe->mnsh_builtin == BOOL_FALSE)
				exit(g_exit_code);
			else
			{
				// 부모에서 builtin으로 pipe 없이 실행한 경우, close 실패하면 동작 어떻게 해야할까? 
				if (m_pipe->out_redirected == BOOL_TRUE)
					ft_close(m_pipe->outfile_fd);
				if (m_pipe->in_redirected == BOOL_TRUE)
					ft_close(m_pipe->infile_fd);
			}
			if (ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, m_pipe, &ft_execute_tree) == FT_ERROR)
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
		// 부모에서 close 실패한 경우, shell은 어떻게 동작하는게 맞을까?
			// close 함수 문서의 왜 실패했을 때 또 닫으면 안되는가? 참조
		else if (pid > 0) // 부모
		{
			printf("getpid() == %d \n", getpid());
			printf("child_pid == %d \n", pid);	
			printf("set_sig IGN before\n");
			set_signal(SIG_IGNORE,SIG_IGNORE); // 자식 프로세스가 진행중일떄는 부모는 시그널 무시
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
		else //에러 출력
			printf("pid error\n");
		pipeline = pipeline->right;
		iter++;
	}
	while (iter != 0)
	{
		wait_child();
		set_signal(SIG_HANDLER, SIG_IGNORE);
		iter--;
	}
	return ;
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

void	execute_builtin(t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (!ft_strcmp(cmd->cmd_name, "echo"))
	{
		printf("execute echo\n");
		ft_echo(cmd, m_pipe);
	}
	if (!ft_strcmp(cmd->cmd_name, "cd"))
	{
		printf("execute cd \n");
		ft_cd(cmd, dll_envp_tower);
	}
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
	{
		printf("execute pwd \n");
		ft_pwd(m_pipe);
	}
	if (!ft_strcmp(cmd->cmd_name, "export"))
	{
		printf("execute export \n");
		ft_export(cmd, dll_envp_tower, m_pipe);
	}
	if (!ft_strcmp(cmd->cmd_name, "unset"))
	{
		printf("execute unset\n");
		ft_unset(cmd, dll_envp_tower);
	}
	if (!ft_strcmp(cmd->cmd_name, "env"))
	{
		printf("execute env \n");
		ft_env(dll_envp_tower, m_pipe);
	}
	if (!ft_strcmp(cmd->cmd_name, "exit"))
	{
		printf("execute exit \n");
		ft_exit(cmd, m_pipe);
	}
	return ;
}

// env에 PATH 안에 명령어를 찾아서 그 경로를 반환
char	**get_env_path(t_detower *dll_envp_tower)
{
	t_d_list	*node;
	int			index;
	char		**env_path_value;
	int			loc;

	node = dll_envp_tower->head;
	index = 0;
	while (node != NULL)
	{
		if (!ft_strcmp(((t_envp_content *)node->content)->key, "PATH"))
			env_path_value = ft_split(
					((t_envp_content *)node->content)->value, ':');
		node = node->next;
	}

	return (env_path_value);
}

void	double_char_free(char **double_char)
{
	int	i;

	i = 0;
	while (double_char[i])
	{
		free(double_char[i]);
		i++;
	}
	free(double_char);
}


// 외부함수 실제 실행
void	execute_external(t_tree_node *node, t_detower *dll_envp_tower, t_pipe *m_pipe)
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
