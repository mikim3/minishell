/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_doubly_linked_list2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:17:40 by kshim             #+#    #+#             */
/*   Updated: 2023/01/06 14:06:18 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

char	*ft_set_new_envp_string(t_d_list *lst_node)
{
	t_env_ctnt		*content;
	char			*ret_str;
	char			*tmp_str;

	content = (t_env_ctnt *)lst_node->content;
	if (content->key == 0)
	{
		if (content->value == 0)
			return (0);
		ret_str = ft_strdup(content->value);
	}
	else if (content->value == 0)
		ret_str = ft_strdup(content->key);
	else
	{
		tmp_str = ft_strjoin(content->key, "=");
		if (tmp_str == 0)
			return (0);
		ret_str = ft_strjoin(tmp_str, content->value);
		free(tmp_str);
	}
	if (ret_str == 0)
		return (0);
	return (ret_str);
}

void	ft_free_t_envp_content(void	*content)
{
	t_env_ctnt	*target;

	target = (t_env_ctnt *)content;
	if (target == 0)
		return ;
	if (target->key != 0)
	{
		free(target->key);
		target->key = 0;
	}
	if (target->value != 0)
	{
		free(target->value);
		target->value = 0;
	}
	free(target);
	return ;
}
