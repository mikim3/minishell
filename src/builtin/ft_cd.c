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

static char	*ft_gethome(t_detower *env_tower)
{
	t_d_list		*env;
	t_env_ctnt		*home_content;
	char			*home_dir;

	env = env_tower->head;
	home_content = find_env_keycmp(env, "HOME");
	if (home_content != NULL)
		home_dir = home_content->value;
	else
		home_dir = NULL;
	return (home_dir);
}

static void	ft_cd_do(t_tree_cmd *cmd, t_detower *env_tower)
{
	char		*tmp;

	if (cmd->cmd_argv[1] == NULL)
	{
		if (ft_gethome(env_tower) == NULL)
			exitcode_with_err("cd", "HOME not set", 1);
		else if (ft_chdir(ft_gethome(env_tower), cmd) == -1)
			return ;
	}
	else if (cmd->cmd_argv[1] != NULL && \
		!ft_strncmp(cmd->cmd_argv[1], "~", 1))
	{
		tmp = ft_strjoin(ft_getenv("HOME"), &cmd->cmd_argv[1][1]);
		if (ft_chdir(tmp, cmd) == -1)
			return (ft_char_free(tmp));
		ft_char_free(tmp);
	}
	else if (cmd->cmd_argv[1] != NULL)
		if (ft_chdir(cmd->cmd_argv[1], cmd) == -1)
			return ;
}

void	ft_cd(t_tree_cmd *cmd, t_detower *env_tower)
{
	char		*pwd_path;

	pwd_path = getcwd(NULL, 0);
	ft_cd_do(cmd, env_tower);
	change_pwd(env_tower, "PWD");
	change_oldpwd(env_tower, pwd_path);
	ft_char_free(pwd_path);
}
