/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 15:07:34 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"


void execute_cmd(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
    
    // 프린트를 안해도 되면 
	if (execute_noprint_builtin(token_tree->content, dll_envp_tower, m_pipe) == 1)
		return ;
	// 출력을 하려면  포크를 해야 됨
    execute_fork(token_tree,dll_envp_tower,m_pipe); 

}

void	execute_fork(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	pid_t	pid;
	pid_t	w_pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		//파이프 관련처리
		if (is_built_in(token_tree->content))
			execute_print_builtin(token_tree->content, dll_envp_tower, m_pipe);
		else
			execute_external(token_tree, dll_envp_tower, m_pipe);
	}
	else if (pid > 0) // 부모
	{
		//자식 프로세스 기다리기, 파이프처리

		wait_child();
	}
	else //에러 출력
		printf("pid error\n");


}

int	is_built_in(t_simple_cmd *simple_cmd)
{
	if (!ft_strcmp(simple_cmd->cmd_name, "cd"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "env"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "export"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "unset"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "pwd"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "echo"))
		return (1);
	if (!ft_strcmp(simple_cmd->cmd_name, "exit"))
		return (1);
	return (0);
}


void	execute_print_builtin(t_simple_cmd *simple_cmd, t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (!ft_strcmp(simple_cmd->cmd_name, "env"))
		// ft_env(simple_cmd, dll_envp_tower, m_pipe);
	if (!ft_strcmp(simple_cmd->cmd_name, "export"))
		// ft_export(simple_cmd, dll_envp_tower, m_pipe);
	if (!ft_strcmp(simple_cmd->cmd_name, "pwd"))
		// ft_pwd(simple_cmd, dll_envp_tower, m_pipe);
	if (!ft_strcmp(simple_cmd->cmd_name, "echo"))
		// ft_echo(simple_cmd, dll_envp_tower, m_pipe);
	return ;
}

// 외부함수 실제 실행
void	execute_external(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	extern	char	**environ;
	
	// 실행 성공시에는 리턴을 받을수가 없다.
	if (execve(((t_simple_cmd *)token_tree->content)->file_path,((t_simple_cmd *)token_tree->content)->argv, environ)== -1)
	{
		//execve실패
		printf("execve 실패 \n");
	}

}

// 프린트 안하는 빌트인 함수 실행
int		execute_noprint_builtin(t_simple_cmd *simple_cmd, t_detower *dll_envp_tower,t_pipe *m_pipe)
{
	if (!ft_strcmp(simple_cmd->cmd_name, "exit"))
	{
		// ft_exit(simple_cmd,dll_envp_tower,m_pipe);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->cmd_name, "unset"))
	{
		// ft_unset(simple_cmd,dll_envp_tower,m_pipe);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->cmd_name, "cd"))
	{
		// ft_cd(simple_cmd,dll_envp_tower,m_pipe);
		return (1);
	}
	// export가 인자가 있으면 출력을 해야만함
	if (!ft_strcmp(simple_cmd->cmd_name, "export") && simple_cmd->argv[1] != NULL)
	{
		// ft_export(simple_cmd,dll_envp_tower,m_pipe);
		return (1);
	}
	return (0);
}



// 
void	wait_child(void)
{
	int		status;
	int		signo;
	int		i;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_code = 128 + signo;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}

	
}
