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

void	ft_pwd(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	char	*output;

	//PWD , OLDPWD
	output = getcwd(NULL, 0); // getcwd가 malloc으로 내부에서 할당해주니까 외부에서 free해줘야함
	output = ft_strjoin(output, ft_strdup("\n")); //
	write(pipe_value->outfile_fd, output, ft_strlen(output));
	free(output);
    //정상 종료 코드
	g_exit_code = 0;
	exit(g_exit_code);
}
