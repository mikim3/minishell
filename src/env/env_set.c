/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:42:02 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 14:40:08 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	set_env(t_detower *env_tower, char *key, char *value)
{
	t_d_list		*env;
	t_env_ctnt		*set_target;

	env = env_tower->head;
	set_target = find_env_keycmp(env, key);
	if (set_target == NULL)
		set_new_env(&(env_tower), key, value);
	else
	{
		free(set_target->key);
		if (set_target->value != NULL)
			free(set_target->value);
		set_env_value(set_target, key, value);
	}
}

void	set_env_value(t_env_ctnt *env, char *key, char *value)
{
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
}

void	set_new_env(t_detower	**env_tower, char	*key, char	*value)
{
	t_d_list		*new_env_list;
	t_env_ctnt		*new_env;

	new_env = env_new();
	if (new_env == 0)
		return ;
	new_env_list = ft_d_lstnew(new_env);
	if (new_env_list == 0)
		return ;
	set_env_value(new_env, key, value);
	ft_deque_add_back(*env_tower, new_env_list);
}

t_env_ctnt	*find_env_keycmp(t_d_list *env, char *env_key)
{
	t_d_list	*my_env;

	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_env_ctnt *)my_env->content)->key, env_key) == 0)
		{
			return (my_env->content);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

t_env_ctnt	*env_new(void)
{
	t_env_ctnt	*new;

	new = malloc(sizeof(t_env_ctnt));
	if (new == 0)
		return (0);
	new->key = NULL;
	new->value = NULL;
	return (new);
}
