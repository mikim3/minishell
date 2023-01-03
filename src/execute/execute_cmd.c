/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 16:53:19 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void execute_cmd(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (is_built_in(token_tree->content))
	{
		if (m_pipe->mnsh_builtin == BOOL_FALSE)
			execute_builtin(token_tree->content, dll_envp_tower, m_pipe, BOOL_FALSE);
		else
			execute_builtin(token_tree->content, dll_envp_tower, m_pipe, BOOL_TRUE);
	}
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

	pipeline = token_tree;
	// 파이프 사전 처리
	iter = 0;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	while (pipeline != 0)
	{
		next_pipe_check(pipeline, m_pipe);
		if (iter == 0 && m_pipe->next_pipe_check == BOOL_FALSE
			&& is_built_in(pipeline->left->right->content) == BOOL_TRUE)
		{
			m_pipe->mnsh_builtin = BOOL_TRUE;
			ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, m_pipe, &ft_execute_tree);
			// execute_builtin(pipeline->left->right->content, dll_envp_tower, m_pipe, BOOL_TRUE);
			return ;
		}
		pid = fork();
		if (pid == 0)
		{	
			ft_putstr_fd("set_sig SIGHANDLER 자식\n",STDERR_FILENO);
			set_signal(SIG_DEFAULT, SIG_DEFAULT); //이게 없으면 SIG_QUIT가 IGN상태이지만  그렇다고 이게 있다고 SIG_CHILD_HANDLER대로 작동하지는 않음 뭘까?
			// 다중 파이프에서 자식 프로세스에게 fork할 때 stdin, out이 없어지지 않는게 나을 것 같음.
			// 이 동작을 다르게 하거나, 필요가 없을지도 모르겠다.
			// 아니면 자식에서 하나? 좀 고민 중
			if (m_pipe->pre_pipe_check == BOOL_TRUE)
			{
				dup2(m_pipe->pre_pipe_read_end, m_pipe->infile_fd);
				close(m_pipe->pre_pipe_read_end);
			}
			if (m_pipe->next_pipe_check == BOOL_TRUE)
			{
				close(m_pipe->pipe[P_READ]);
				dup2(m_pipe->pipe[P_WRITE], m_pipe->outfile_fd);
				close(m_pipe->pipe[P_WRITE]);
			}
			ft_tree_node_pre_traversal2(pipeline->left, dll_envp_tower, m_pipe, &ft_execute_tree);
		}
		else if (pid > 0) // 부모
		{
			printf("getpid() == %d \n", getpid());
			printf("child_pid == %d \n", pid);	
			printf("set_sig IGN before\n");
			set_signal(SIG_IGNORE,SIG_IGNORE); // 자식 프로세스가 진행중일떄는 부모는 시그널 무시
			// 이전 포크 파이프 처리
			if (m_pipe->pre_pipe_check == BOOL_TRUE)
			{
				close(m_pipe->pre_pipe_read_end);
				m_pipe->pre_pipe_check = BOOL_FALSE;
			}
			// 파이프 사후 처리
			if (m_pipe->next_pipe_check == BOOL_TRUE)
			{
				close(m_pipe->pipe[P_WRITE]);
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
	//자식 프로세스 기다리기,
	while (iter != 0)
	{
		wait_child();
		set_signal(SIG_HANDLER,SIG_IGNORE);
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

void	execute_builtin(t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe, int from_mnsh)
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
	if (from_mnsh == BOOL_FALSE)
		exit(g_exit_code);
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
		if(!ft_strcmp(((t_envp_content *)node->content)->key, "PATH"))
		{
			env_path_value = ft_split(((t_envp_content *)node->content)->value, ':');
		}
		node = node->next;
	}

	return (env_path_value);
}

void	double_char_free(char **double_char)
{
	int	i;

	i = 0;
	while(double_char[i])
	{
		free(double_char[i]);
		i++;
	}
	free(double_char);
}

char	*get_file_path_from_env_path(char *command,t_detower *dll_envp_tower)
{
	char	*file_path;
	char	**env_path_values;
	char	*tmp;
	int		index;

	file_path = NULL;
	// key가 PATH인 환경변수의 value값을 split(:)으로 나누어서 env_path_values에 저장
	env_path_values = get_env_path(dll_envp_tower);
	
	index = 0;
	while(env_path_values[index])
	{
		tmp = ft_strjoin("/", command);
		file_path = ft_strjoin(env_path_values[index], tmp);
		// 파일의 존재여부 확인, 실행권한 확인
		if (access(file_path,X_OK) == -1)
		{
			free(file_path);
			// file_path = NULL;
		}
		else
			break ;
		index++;
	}

	if (env_path_values)  
		// 이차원배열 free 있는지 찾아보고 없으면 함수 만들기
		ft_free_string_ptr_arr(env_path_values);

	return	(file_path);
}

char	*set_file_path(char *command, t_detower *dll_envp_tower)
{
	char	*file_path;
	char	*current_path;

	
	if (ft_strncmp(command, "/", 1) == 0) // 절대경로는 그대로 준다.
	{
		file_path = ft_strdup(command);
	}
	else if (ft_strncmp("./", command, 2) == 0) // 상대경로 ./bash_exe_ex hahaha 현재경로에 bash를 실행한다고 생각  
	{
		command = ft_substr(command, 2, ft_strlen(command) - 2);
		current_path = getcwd(NULL, 0);
		file_path = ft_strjoin_infree(current_path, ft_strdup("/"));
		file_path = ft_strjoin_infree(file_path, ft_strdup(command));
	}
	else // 환경변수 PATH에 세팅되어서 명령어로 실행할수 있는 명령어
	{
		printf(" 명령어 \n");
		// PATH=/Users/mikim3/brew/bin:/Users/mikim3/goinfre/brew/bin:/usr/local/bin 
		// :/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
		// (:)콜론으로 구분된다.
		// 절대경로로 PATH안에 있는 값들에 해당하는 폴더까지 간 다음에 해당 명령어에 해당하는 파일이 있는지 확인
		// 없으면 다음 : 확인 반복
		file_path = get_file_path_from_env_path(command, dll_envp_tower);
	}
	return (file_path);
}

// 외부함수 실제 실행
void	execute_external(t_tree_node *node,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	char			*file_path;
	char			**env;

	file_path = set_file_path(((t_tree_cmd *)node->content)->cmd_name, dll_envp_tower);
	env = ft_set_char_envp_from_dll(dll_envp_tower,0);

	ft_execve(file_path,((t_tree_cmd *)node->content)->cmd_argv, env);
	//필요한지 다시 생각해보기
	if (!file_path)
		free(file_path);
	
}
