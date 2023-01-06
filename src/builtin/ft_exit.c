/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:16:16 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 18:21:44 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	g_exit_code = 0;
	ft_putendl_fd("exit", pipe_value->outfile_fd);
	if (cmd->cmd_argv[1] == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		exit(g_exit_code);
	}
	else if (cmd->cmd_argv[2] == NULL)
	{
		g_exit_code = (unsigned char)ft_atoi(cmd->cmd_argv[1]);
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		printf("in child - %d\n", g_exit_code);
		exit(g_exit_code);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}
