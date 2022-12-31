/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:58:13 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 15:36:1ß by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 키값에는 무조건 문자열로만 이루어져야한다. '='나 숫자로 시작하면 오류다.
// 
#include "../../include/ft_minishell.h"

void	ft_export(t_tree_cmd *cmd, t_detower *env_tower, t_pipe *pipe_value)
{
	int		    index;
	char	    *key;
	char	    *value;
	char	    *output;
    t_d_list    *env;

    env = env_tower->head;

	index = 0;
	if (cmd->cmd_argv[1] == NULL) // export 명령만 들어온경우
	{
		output = show_env_in_export(env);  // 출력해야할 값 출력
		write(pipe_value->outfile_fd, output, ft_strlen(output));
		g_exit_code = 0;
		exit(0);
	}
	// export a=10 b=20
	// =을 기준으로 key,value가 나뉘어진다.
	// check_env_key로 올바른 env
	// ex) bash-3.2$ export b+_=
	//bash: export: `b+_=': not a valid identifier
	// 키값으로 
	while (cmd->cmd_argv[++index])
	{
		key = NULL;
		value = NULL;
		//
		div_key_value(cmd->cmd_argv[index], &key, &value); //
		if (check_env_key(key))
		{
			env_key_error("export", key);
			printf("check_env_key return 1  ERROR\n");
		}
		else
			set_env(env_tower, key, value);
		free(key);
		free(value);
	}
	g_exit_code = 0;
	system("leaks minishell | grep LEAK");
}

char	*show_env_in_export(t_d_list	*env)
{
    char    *output;
    char    *line;

	line = NULL;
	output = NULL;

	while (env)
	{
		if (((t_envp_content *)env->content)->value != NULL)
		{
			line = ft_strjoin_infree(strdup("declare -x "), ((t_envp_content *)env->content)->key);
			line = ft_strjoin_infree(line, ft_strdup("=\""));
			line = ft_strjoin_infree(line, (((t_envp_content *)env->content)->value));
			line = ft_strjoin_infree(line, ft_strdup("\"\n"));	
			output = ft_strjoin_infree(output, line);
		}
		else
		{
			line = ft_strjoin_infree(strdup("declare -x "), ((t_envp_content *)env->content)->key);
			line = ft_strjoin_infree(line, ft_strdup("\n"));	
			output = ft_strjoin_infree(output, line);
		}
		
		env = env->next;
	}
    return (output);
}

void	div_key_value(char *arg, char **key, char **value)
{
	int	index;

	index = 0;
	if (arg[0] == '=')
		return ;
	while (arg[index] && arg[index] != '=' )
		index++;
	*key = ft_substr(arg, 0, index);
	// 길이가  index보다 크면 즉 value가 존재하면 값넣고 값 없어도 NULL넣어줘야함
	if (ft_strlen(arg) - index)
		*value = ft_substr(arg, index + 1, ft_strlen(arg) - index);
	else
		*value = NULL;
}
