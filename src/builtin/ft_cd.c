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
	g_exit_code = 0;
	change_pwd_oldpwd(env_tower, "OLDPWD"); //실패했을때 경로를 미리 바꾸지 않게 만들기
	if (cmd->cmd_argv[1] != NULL)
		ft_chdir(cmd->cmd_argv[1]);

	change_pwd_oldpwd(env_tower, "PWD");
}
