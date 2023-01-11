/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/11 15:04:04 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_execve(char *file, char **argv, char **envp)
{
	if (execve(file, argv, envp) == -1)
	{
		if (ft_strncmp(argv[0], "/", 1) == 0 || \
			ft_strncmp(argv[0], "./", 2) == 0)
		{
			if (errno == ENOENT)
				exitcode_with_err(argv[0], strerror(errno), 127);
			else if (errno == EACCES)
				exitcode_with_err(argv[0], strerror(errno), 126);
			else
				exitcode_with_err(argv[0], strerror(errno), 1);
		}
		else
			exitcode_with_err(argv[0], "command not found", 127);
	}
	return ;
}

int	ft_chdir(char *dir, t_tree_cmd *cmd)
{
	int		return_value;

	return_value = chdir(dir);
	if (return_value == -1)
	{
		if (errno == ENOENT)
			exitcode_with_err2("cd", cmd->cmd_argv[1], strerror(errno), 127);
		else if (errno == EACCES)
			exitcode_with_err2("cd", cmd->cmd_argv[1], strerror(errno), 126);
		else
			exitcode_with_err2("cd", cmd->cmd_argv[1], strerror(errno), 1);
	}
	return (return_value);
}

int	ft_access(char *file, int flags)
{
	int	ret_val;

	ret_val = access(
			file, flags);
	if (ret_val == -1)
		exitcode_with_err(file, strerror(errno), 1);
	return (ret_val);
}
