/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/29 17:25:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

char	*get_file_path_from_env_path(char *command, t_detower *dll_envp_tower)
{
	char	*file_path;
	char	**env_path_values;
	char	*tmp;
	int		index;

	file_path = NULL;
	// key가 PATH인 환경변수의 value값을 split(:)으로 나누어서 env_path_values에 저장
	env_path_values = get_env_path(dll_envp_tower);
	index = 0;
	while (env_path_values[index])
	{
		tmp = ft_strjoin("/", command);
		file_path = ft_strjoin(env_path_values[index], tmp);
		if (access(file_path, X_OK) == -1)
		{
			free(file_path);
		}
		else
			break ;
		index++;
	}
	if (env_path_values)
		ft_free_string_ptr_arr(env_path_values);
	return (file_path);
}

char	*set_file_path(char *command, t_detower *dll_envp_tower)
{
	char	*file_path;
	char	*current_path;

	if (ft_strncmp(command, "/", 1) == 0)
	{
		file_path = ft_strdup(command);
	}
	else if (ft_strncmp("./", command, 2) == 0)
	{
		command = ft_substr(command, 2, ft_strlen(command) - 2);
		current_path = ft_getcwd(NULL, 0);
		if (current_path == NULL)  // 이래도 괜찮나???? // 외부함수 실행에만 쓴다면 exit()걍써도 괜찮을지도
			return (NULL);
		file_path = ft_strjoin_infree(current_path, ft_strdup("/"));
		file_path = ft_strjoin_infree(file_path, ft_strdup(command));
	}
	else
	{
		file_path = get_file_path_from_env_path(command, dll_envp_tower);
	}
	return (file_path);
}

char	**get_env_path(t_detower *dll_envp_tower)
{
	t_d_list	*node;
	int			index;
	char		**env_path_value;
	int			loc;

	node = dll_envp_tower->head;
	index = 0;
	while (node != NULL)
	{
		if (!ft_strcmp(((t_env_ctnt *)node->content)->key, "PATH"))
			env_path_value = ft_split(
					((t_env_ctnt *)node->content)->value, ':');
		node = node->next;
	}
	return (env_path_value);
}
