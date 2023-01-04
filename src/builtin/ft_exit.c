/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:16:16 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 18:44:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	g_exit_code = 0;
	ft_putendl_fd("exit", pipe_value->outfile_fd);
	if (cmd->cmd_argv[1] == NULL)
		exit(g_exit_code);
	g_exit_code = ft_atoi(cmd->cmd_argv[1]);
	if (cmd->cmd_argv[2] != NULL)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
	}
	exit(g_exit_code);
}
