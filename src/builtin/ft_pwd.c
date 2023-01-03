/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:14:33 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 14:59:07 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// $OLDPWD 생각해보기

#include "../../include/ft_minishell.h"

void	ft_pwd(t_pipe *pipe_value)
{
	char	*output;

	g_exit_code = 0;
	output = getcwd(NULL, 0);
	if (output == NULL)
	{
		output = ft_strjoin_infree(ft_strdup(strerror(errno)),ft_strdup("\n"));
		// 종료코드 설정구현하기
		g_exit_code = 1;  
		free(output); //  free 하던 안하던 괜찮음
		exit(1);
	}
	//  릭 변경 완료   다시 체크해보기
	output = ft_strjoin_infree(output, ft_strdup("\n")); //
	write(pipe_value->outfile_fd, output, ft_strlen(output));
	free(output);
    //정상 종료 코드
	exit(g_exit_code);
}
