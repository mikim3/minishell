/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:15 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 14:59:28 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_cd(t_tree_cmd *cmd,t_detower *env_tower ,t_pipe *pipe_value)
{
	int		return_value;
	char	*output;

	//OLDPWD
	return_value = chdir(cmd->cmd_argv[1]); //실패시 -1리턴
	// 상대경로 테스트하기  // 
	// PWD의 환경변수를 set해주기 

	change_PWD_OLDPWD(env_tower);
	output = ft_strjoin(ft_strdup(strerror(errno)),ft_strdup("\n"));  // strdup해야 되는지 헷갈리네
	if (return_value == -1)
		write(STDERR_FILENO, output, ft_strlen(output) + 1);
	if (output)
		free(output);
	g_exit_code = 0;

}
