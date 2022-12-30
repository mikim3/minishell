/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:58:13 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 15:21:09 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 키값에는 무조건 문자열로만 이루어져야한다. '='나 숫자로 시작하면 오류다.
// 

// 순서 대로 출력 해야되는데 그걸 처리하려면
// env값을 새로고침 할때 그 값이 순서대로 들어가게끔 한다?
// 
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
		write(STDOUT_FILENO, output, ft_strlen(output));
		// write(pipe_value->outfile_fd, output, ft_strlen(output));
		// g_exit_code = 0;
		exit(0);
	}
	// export a=10 b=20
	// =을 기준으로 key,value가 나뉘어진다.
	// check_env_key로 올바른 env
	// ex) bash-3.2$ export b+_=
	//bash: export: `b+_=': not a valid identifier
	// 키값으로 
	while (cmd->cmd_argv[++index])
	{
		key = NULL;
		value = NULL;
		//
		div_key_value(cmd->cmd_argv[index], &key, &value); //
		printf("key == %s value === %s \n",key,value);
		if (check_env_key(key))
		{
			printf("check_env_key return 1  ERROR\n");
			exit(1);
		}
		set_env(env_tower, key, value);
		free(key);
		free(value);
	}
	g_exit_code = 0;
	system("leaks minishell | grep LEAK");
}

char	*show_env_in_export(t_d_list	*env)
{
    char    *output;
    char    *line;

	line = NULL;
	output = NULL;

	while (env->next)
	{
		line = ft_strjoin_infree(strdup("declare -x "), ((t_envp_content *)env->content)->key);
		line = ft_strjoin_infree(line, ft_strdup("="));
		line = ft_strjoin_infree(line, (((t_envp_content *)env->content)->value));
		line = ft_strjoin_infree(line, ft_strdup("\n"));	
		output = ft_strjoin_infree(output, line);
		env = env->next;
	}
    return (output);
}

void	div_key_value(char *arg, char **key, char **value)
{
	int	index;

	index = 0;
	while (arg[index] && arg[index] != '=' )
		index++;
	*key = ft_substr(arg, 0, index);
	// 길이가  index보다 크면 즉 value가 존재하면 값넣고 값없어도 NULL넣어줘야함
	if (ft_strlen(arg) - index)
		*value = ft_substr(arg, index + 1, ft_strlen(arg) - index);
	else
		*value = NULL;
}

// 해당 키값이 존재하는 키인지 확인
// 존재하지 않으면 set_new_env
// 존재한다면 기존값 수정하기 set_modifiy


// void				ft_deque_add_front(t_detower *detower, t_d_list *new_elem);
// 위에 함수 잘써먹어보기
void	set_env(t_detower *env_tower, char *key, char *value)
{
	t_d_list		*env;
	t_envp_content	*set_target;

	env = env_tower->head;
	//
	set_target = find_env_keycmp(env, key);
	
	printf("set_target->key %s\n");

	// set_new_env는 새로운 노드도 추가해야함
	if (set_target == NULL)
		set_new_env(env_tower, key, value);
	else if (value != NULL)
	{
		free(set_target->key);
		if (set_target->value != NULL)
			free(set_target->value);
		set_env_value(set_target, key, value);
	}
}

t_envp_content	*find_env_keycmp(t_d_list *env, char *env_key)
{
	t_d_list	*my_env;

	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_envp_content *)my_env->content)->key, env_key) == 0)
			return (my_env->content);
		my_env = my_env->next;
	}
	return (NULL);
}

void	set_env_value(t_envp_content *env, char *key, char *value)
{
	//value가 존재한다면 value
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
}







// void	set_new_env(t_detower	*env_tower, char	*key, char	*value)
// {
// 	t_list		*new_list;
// 	t_d_list	*new_contets;
// 	char	*origin_text;

// 	new_contets = envnew();
// 	new_list = ft_lstnew(new_contets);
// 	if (new_list == NULL || origin_text == NULL || new_contets == NULL)
// 		allocation_error();
// 	set_env_value(new_contets, key, value);

// 	ft_lstadd_back(env, new_list);

// }

// t_env	*envnew(void)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (new == NULL)
// 		return (NULL);
// 	new->origin_text = NULL;
// 	new->key = NULL;
// 	new->value = NULL;
// 	return (new);
// }