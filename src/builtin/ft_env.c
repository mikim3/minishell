/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:16:11 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/29 18:16:31 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

// 어떤 상황에 어떤 종료코드를 넣는게 가장 옳을지 좀더 고민이 필요함

void	ft_env(t_tree_cmd *cmd, t_env *env, t_pipe *pipe_value)
{
	char	*output;
	char	*line;

	line = NULL;
	output = NULL;
	while (env) //이게 맞나??
	{
		if (env->value == NULL) 
		{
			env = env->next;
			continue ;
		}
		line = ft_strjoin(ft_strdup(env->key), ft_strdup("="));
		line = ft_strjoin(ft_strdup(env->value), ft_strdup("\n"));
		output = ft_strjoin(output, line);
		env = env->next;
	}
	write(mini->outfile_fd, output, ft_strlen(output));
	free(output);
	g_exit_code = 0;
	exit(g_exit_code);

	system("leaks minishell | grep LEAK");

}
