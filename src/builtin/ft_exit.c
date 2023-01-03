/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:16:16 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 11:13:02 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
    // exit는 일단 출력
	ft_putendl_fd("exit", STDOUT_FILENO);
    // ex) mini $>  exit      인자없는경우
	if (cmd->cmd_argv[1] == NULL)
		exit(g_exit_code);  // 그냥 종료하고 상태코드 반환
	g_exit_code = ft_atoi(cmd->cmd_argv[1]);  // 상태코드 저장
	
	if (cmd->cmd_argv[2] != NULL)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	else
	{
		exit(g_exit_code);
	}
}
