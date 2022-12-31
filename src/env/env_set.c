/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:42:02 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/26 15:14:19 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

// 해당 키값이 존재하는 키인지 확인
// 존재하지 않으면 set_new_env
// 존재한다면 기존값 수정하기 
void	set_env(t_detower *env_tower, char *key, char *value)
{
	t_d_list		*env;
	t_envp_content	*set_target;

	env = env_tower->head;
	set_target = find_env_keycmp(env, key);  

	if (set_target == NULL)
	{
		set_new_env(&(env_tower), key, value);
	}
	else
	{
		free(set_target->key);
		if (set_target->value != NULL)
			free(set_target->value);
		set_env_value(set_target, key, value);
	}
}

void	set_env_value(t_envp_content *env, char *key, char *value)
{
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
}

// env_tower에 새로운 key,value를 가진 t_envp_content를 가진 env_list를 추가한다.
void	set_new_env(t_detower	**env_tower, char	*key, char	*value)
{
	t_d_list		*new_env_list;
	t_envp_content	*new_env;

	// 새로운 env를 만든다.
	new_env = env_new();
	//새로운 env_list를 멀록하고 새 값을 넣는다.
	new_env_list = ft_d_lstnew(new_env);
	if (new_env_list == NULL || new_env == NULL)
	{
		printf("new_env_list == NULL || new_env == NULL \n");
	}
	// new_env안에 key와 value를 넣는다.
	set_env_value(new_env, key, value);
	// env_tower에  new_env_list넣기
	ft_deque_add_back(*env_tower,new_env_list);
}

t_envp_content	*find_env_keycmp(t_d_list *env, char *env_key)
{
	t_d_list	*my_env;

	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_envp_content *)my_env->content)->key, env_key) == 0)
		{
			return (my_env->content);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

t_envp_content	*env_new(void)
{
	t_envp_content	*new;

	new = malloc(sizeof(t_envp_content));
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	return (new);
}


// void	test_tree_node_check_for_content(void *tree_node)
// {
// 	t_tree_node *node;
// 	int	i;

// 	i = 0;
// 	node = (t_tree_node *)tree_node;
// 	if (node->type == NODE_CMD)
// 	{
// 		if (node->content == 0)
// 			return ;
// 		printf("node_cmd_name : %s\n", ((t_tree_cmd *)node->content)->cmd_name);
// 		while (((t_tree_cmd *)node->content)->cmd_argv[i] != 0)
// 		{
// 			printf("node_cmd_argv : %s\n", ((t_tree_cmd *)node->content)->cmd_argv[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	else if (node->type == NODE_REDIR
// 		|| node->type == NODE_FD_REDIR)
// 	{
// 		if (node -> content == 0)
// 			return ;
// 		printf("node_redir : %s\n", ((t_tree_redir *)node->content)->redir);
// 		printf("node_file_name : %s\n", ((t_tree_redir *)node->content)->file_name);
// 	}
// 	return ;
// }



