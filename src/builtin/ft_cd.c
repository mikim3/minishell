/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:15 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 11:49:58 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_cd(t_tree_cmd *cmd,t_detower *env_tower)
{
	int		return_value;
	char	*output;

	g_exit_code = 0;
	change_pwd_oldpwd(env_tower, "OLDPWD");
	return_value = 0;
	if (cmd->cmd_argv[1] != NULL)
		return_value = chdir(cmd->cmd_argv[1]); //실패시 -1리턴
	change_pwd_oldpwd(env_tower, "PWD");
	output = ft_strjoin_infree(ft_strdup(strerror(errno)),ft_strdup("\n"));
	if (return_value == -1)
	{
		write(STDERR_FILENO, output, ft_strlen(output) + 1);
		g_exit_code = 1;
	}
	if (output)
		free(output);
}
