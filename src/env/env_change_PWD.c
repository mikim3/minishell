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

void	change_PWD_OLDPWD(t_detower *env_tower)
{
	t_d_list		*env;
	t_envp_content	*set_pwd;
	t_envp_content	*set_OLDPWD;
	char			*pwd_path;

	pwd_path = getcwd(NULL, 0); // getcwd가 malloc으로 내부에서 할당해주니까 외부에서 free해줘야함

	env = env_tower->head;
	set_pwd = find_env_keycmp(env, "PWD");
	if (set_pwd != NULL)
	{
		free(set_pwd->key);
		if (set_pwd->value != NULL)
			free(set_pwd->value);
		set_env_value(set_pwd, "PWD", pwd_path);
	}
	free(pwd_path);
}
