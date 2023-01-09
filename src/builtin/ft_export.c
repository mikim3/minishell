/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:58:13 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 20:57:33 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

static char	*show_env_in_export(t_d_list	*env)
{
	char	*output;
	char	*line;

	line = NULL;
	output = NULL;
	while (env)
	{
		if (((t_env_ctnt *)env->content)->value != NULL)
		{
			line = ft_strdup(((t_env_ctnt *)env->content)->key);
			line = ft_strjoin_infree(line, ft_strdup("=\""));
			line = ft_strjoin_infree(line,
					ft_strdup((((t_env_ctnt *)env->content)->value)));
			line = ft_strjoin_infree(line, ft_strdup("\"\n"));
			output = ft_strjoin_infree(output, line);
		}
		else
		{
			line = ft_strdup(((t_env_ctnt *)env->content)->key);
			line = ft_strjoin_infree(line, ft_strdup("\n"));
			output = ft_strjoin_infree(output, line);
		}
		env = env->next;
	}
	return (output);
}

static void	ft_export_while(t_tree_cmd *cmd, t_detower *env_tower)
{
	char		*key;
	char		*value;
	int			index;

	index = 0;
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

void	ft_export(t_tree_cmd *cmd, t_detower *env_tower, t_pipe *pipe_value)
{
	char		*output;
	t_d_list	*env;

	env = env_tower->head;
	if (cmd->cmd_argv[1] == NULL)
	{
		output = show_env_in_export(env);
		write(pipe_value->outfile_fd, output, ft_strlen(output));
		free(output);
	}
	else
		ft_export_while(cmd, env_tower);
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
	if (ft_strlen(arg) - index)
		*value = ft_substr(arg, index + 1, ft_strlen(arg) - index);
	else
		*value = NULL;
	return (FT_SUCCESS);
}
