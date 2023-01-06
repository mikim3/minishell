/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:17:03 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 14:26:32 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_unset(t_tree_cmd *cmd, t_detower *env_tower)
{
	int		index;
	char	*key;

	index = 1;
	g_exit_code = 0;
	if (cmd->cmd_argv[1] == NULL)
		return ;
	while (cmd->cmd_argv[index])
	{
		key = cmd->cmd_argv[index];
		if (check_env_key(key))
			env_key_error("unset", key);
		else
			unset_env(env_tower, key);
		index++;
	}
}

void	unset_env(t_detower *env_tower, char *key)
{
	t_d_list			*env_list;
	t_d_list			*prev;

	env_list = env_tower->head;
	prev = NULL;
	if (key == NULL)
		return ;
	else
	{
		while (env_list)
		{
			if (ft_strcmp(((t_env_ctnt *)env_list->content)->key, key) == 0)
			{
				delete_t_d_list(env_tower, env_list, prev);
				return ;
			}
			prev = env_list;
			env_list = env_list->next;
		}
	}
}

void	delete_t_d_list(t_detower *env_tower, t_d_list	*env, t_d_list	*prev)
{
	if (prev == NULL)
	{
		env_tower->head = env->next;
		free_env_list(&env);
	}
	else if (env->next == NULL)
	{
		prev->next = env->next;
		env_tower->tail = prev;
		free_env_list(&env);
	}
	else
	{
		prev->next = env->next;
		free_env_list(&env);
	}
}

void	free_env_list(t_d_list **target)
{
	free(((t_env_ctnt *)((*target)->content))->key);
	if (((t_env_ctnt *)((*target)->content))->value != NULL)
		free(((t_env_ctnt *)((*target)->content))->value);
	free(((*target)->content));
	(*target)->next = NULL;
	free(*target);
}
