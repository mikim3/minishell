/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 14:06:46 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	// 권한 에러는 execve실행전에 확인됨
	if (execve(file, argv, envp) == -1)
	{
		printf("%d \n",errno);
		// if (errno == 2) //  No such file or directory
		exitcode_with_err("execve()", strerror(errno), 127);
	}
	return ;
}
