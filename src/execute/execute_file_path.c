/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 18:48:38 by kshim            ###   ########.fr       */
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
	env_path_values = get_env_path(dll_envp_tower);
	index = 0;
	while (env_path_values[index])
	{
		tmp = ft_strjoin("/", command);
		file_path = ft_strjoin(env_path_values[index], tmp);
		free(tmp);
		if (access(file_path, X_OK) == -1)
		{
			free(file_path);
			file_path = 0;
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
		if (current_path == NULL)
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

	node = dll_envp_tower->head;
	index = 0;
	env_path_value = 0;
	while (node != NULL)
	{
		if (!ft_strcmp(((t_env_ctnt *)node->content)->key, "PATH"))
			env_path_value = ft_split(
					((t_env_ctnt *)node->content)->value, ':');
		node = node->next;
	}
	return (env_path_value);
}
