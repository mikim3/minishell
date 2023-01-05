/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change_PWD.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:47 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 13:14:28 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	change_pwd(t_detower *env_tower, char *select)
{
	t_d_list		*env;
	t_env_ctnt	*set_pwd;
	char			*pwd_path;

	pwd_path = ft_getcwd(NULL, 0);
	if (pwd_path == NULL)
		return ;
	env = env_tower->head;
	set_pwd = find_env_keycmp(env, select);
	if (set_pwd != NULL)
	{
		free(set_pwd->key);
		if (set_pwd->value != NULL)
			free(set_pwd->value);
		set_env_value(set_pwd, select, pwd_path);
	}
	free(pwd_path);
}

void	change_oldpwd(t_detower *env_tower, char *get_cwd)
{
	t_d_list		*env;
	t_env_ctnt	*set_pwd;

	env = env_tower->head;
	set_pwd = find_env_keycmp(env, "OLDPWD");
	if (set_pwd != NULL)
	{
		free(set_pwd->key);
		if (set_pwd->value != NULL)
			free(set_pwd->value);
		set_env_value(set_pwd, "OLDPWD", get_cwd);
	}
}
