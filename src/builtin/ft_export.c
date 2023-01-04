/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:58:13 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 16:49:41 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 키값에는 무조건 문자열로만 이루어져야한다. '='나 숫자로 시작하면 오류다.
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
	}
	while (cmd->cmd_argv[++index])
	{
		key = NULL;
		value = NULL;
		if (div_key_value(cmd->cmd_argv[index], &key, &value) == FT_ERROR)
			env_key_error("export", cmd->cmd_argv[index]);
		else
		{
			if (check_env_key(key))
				env_key_error("export", key);
			else
				set_env(env_tower, key, value);
		}
		if (key)
			free(key);
		if (value)
			free(value);
	}
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
			line = ft_strjoin_infree(ft_strdup("declare -x "), ft_strdup(((t_envp_content *)env->content)->key));
			line = ft_strjoin_infree(line, ft_strdup("=\""));
			line = ft_strjoin_infree(line, ft_strdup((((t_envp_content *)env->content)->value)));
			line = ft_strjoin_infree(line, ft_strdup("\"\n"));	
			output = ft_strjoin_infree(output, line);
		}
		else
		{
			line = ft_strjoin_infree(strdup("declare -x "), ft_strdup(((t_envp_content *)env->content)->key));
			line = ft_strjoin_infree(line, ft_strdup("\n"));	
			output = ft_strjoin_infree(output, line);
		}
		env = env->next;
	}
    return (output);
}

int	div_key_value(char *arg, char **key, char **value)
{
	int	index;

	index = 0;
	if (arg[0] == '=')
		return (FT_ERROR);
	while (arg[index] && arg[index] != '=' )
		index++;
	*key = ft_substr(arg, 0, index);
	// 길이가  index보다 크면 즉 value가 존재하면 값넣고 값 없어도 NULL넣어줘야함
	if (ft_strlen(arg) - index)
		*value = ft_substr(arg, index + 1, ft_strlen(arg) - index);
	else
		*value = NULL;
	return (FT_SUCCESS);
}
