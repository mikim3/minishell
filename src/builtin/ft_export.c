/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:58:13 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/29 19:47:49 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 키값에는 무조건 문자열로만 이루어져야한다. '='나 숫자로 시작하면 오류다.
// 

// 순서 대로 출력 해야되는데 그걸 처리하려면
// env값을 새로고침 할때 그 값이 순서대로 들어가게끔 한다?
// 
#include "../../include/ft_minishell.h"


// void	ft_export(t_tree_cmd *cmd, t_d_list *env, t_pipe *pipe_value)
// {
// 	int		index;
// 	char	*key;
// 	char	*value;
// 	char	*output;

// 	index = 0;
// 	if (cmd->cmd_argv[1] == NULL) // export 명령만 들어온경우
// 	{
// 		output = show_env_use_export(env);  // 출력해야할 값 출력
// 		write(pipe_value->outfile_fd, output, ft_strlen(output));
// 		// g_exit_code = 0;
// 		exit(0);
// 	}
	
// 	while (cmd->cmd_argv[++index])
// 	{
// 		key = NULL;
// 		value = NULL;
// 		div_key_value(cmd->cmd_argv[index], &key, &value); //
// 		if (check_env_key(key))
// 			env_key_error("export", key);// 
// 		else
// 			set_env(&env, key, value);
// 		free(key);
// 		free(value);
// 	}
// 	g_exit_code = 0;
// }

