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

void	ft_cd(t_tree_cmd *cmd, t_detower *env_tower)
{
	char		*pwd_path;
	char		*tmp;

	pwd_path = ft_getcwd(NULL, 0);
	if (pwd_path == NULL)
		return ;
	if (!ft_strcmp(cmd->cmd_argv[1], "~"))
	{
		tmp = ft_strjoin(ft_gethome(env_tower), &cmd->cmd_argv[1][1]);
		if (ft_chdir(tmp, cmd) == -1)
			return (free(pwd_path), free(tmp));
		if (tmp)
			free(tmp);
	}
	else if (cmd->cmd_argv[1] != NULL)
		if (ft_chdir(cmd->cmd_argv[1], cmd) == -1)
			return (free(pwd_path));
	change_pwd(env_tower, "PWD");
	change_oldpwd(env_tower, pwd_path);
	if (pwd_path)
		free(pwd_path);
}
