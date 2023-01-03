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

	//OLDPWD
	change_pwd_oldpwd(env_tower, "OLDPWD");
	return_value = 0;
	if (cmd->cmd_argv[1] != NULL)
	{
		return_value = chdir(cmd->cmd_argv[1]); //실패시 -1리턴
	}
	else // ex) cd  만 들어온 상황 이경우 cd $HOME으로 가기  그걸 만들때 $HOME이 없는 경우 생각하기
	{
		// $HOME 파싱하기
		// return_value = chdir($HOME이거 같넣기); //실패시 -1리턴
	}
	// PWD의 환경변수를 set해주기 
	change_pwd_oldpwd(env_tower, "PWD");
	output = ft_strjoin_infree(ft_strdup(strerror(errno)),ft_strdup("\n"));
	if (return_value == -1)
	{
		write(STDERR_FILENO, output, ft_strlen(output) + 1);
		g_exit_code = 1;
	}
	if (output)
		free(output);
	//cd 안에서 오류가 나지 않았다면
	if (g_exit_code != 1)
		g_exit_code = 0;
}
