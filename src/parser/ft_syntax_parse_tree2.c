/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_parse_tree2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:24:51 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 16:11:46 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

t_tree_rdr	*ft_node_content_redir(t_list **token)
{
	t_tree_rdr	*redir_node;

	redir_node = (t_tree_rdr *)malloc(sizeof(t_tree_rdr));
	if (redir_node == 0)
		return (0);
	redir_node->redir = ft_strdup(ft_token_str(*token));
	if (redir_node->redir == 0)
		return (0);
	*token = (*token)->next;
	redir_node->file_name = ft_strdup(ft_token_str(*token));
	if (redir_node->file_name == 0)
		return (0);
	return (redir_node);
}

int	ft_syntax_parse_cmd(t_list **token, t_tree_node *cmd)
{
	if (cmd->content == 0)
	{
		cmd->content = (t_tree_cmd *)malloc(sizeof(t_tree_cmd));
		if (cmd->content == 0)
			return (exitcode_with_err("malloc", strerror(errno), 140), \
				FT_ERROR);
		((t_tree_cmd *)(cmd->content))->cmd_name
			= ft_strdup(ft_token_str(*token));
		if (((t_tree_cmd *)(cmd->content))->cmd_name == 0)
			return (exitcode_with_err("malloc", strerror(errno), 140), \
				FT_ERROR);
		((t_tree_cmd *)(cmd->content))->cmd_argv = 0;
	}
	((t_tree_cmd *)(cmd->content))->cmd_argv
		= ft_set_cmd_argv(
			&(((t_tree_cmd *)(cmd->content))->cmd_argv), ft_token_str(*token));
	if (((t_tree_cmd *)(cmd->content))->cmd_argv == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	return (FT_SUCCESS);
}

char	**ft_set_cmd_argv(char ***argv, char *str)
{
	int		iter;
	char	**new_argv;

	new_argv = ft_set_cmd_argv_set_new_argv(argv, str);
	if (new_argv == 0)
		return (0);
	if (*argv == 0)
		return (new_argv);
	iter = 0;
	while ((*argv)[iter] != 0)
	{
		new_argv[iter] = ft_strdup((*argv)[iter]);
		if (new_argv[iter] == 0)
		{
			ft_free_string_ptr_arr(new_argv);
			return (0);
		}
		iter++;
	}
	ft_free_string_ptr_arr(*argv);
	return (new_argv);
}

char	**ft_set_cmd_argv_set_new_argv(char ***argv, char *str)
{
	int		argv_size;
	char	**new_argv;

	argv_size = 1;
	if (*argv != 0)
	{
		while ((*argv)[argv_size - 1] != 0)
			argv_size++;
	}
	new_argv = ft_calloc((argv_size + 1), sizeof(char *));
	if (new_argv == 0)
		return (0);
	new_argv[argv_size] = 0;
	new_argv[argv_size - 1] = ft_strdup(str);
	if (new_argv[argv_size - 1] == 0)
	{
		ft_free_string_ptr_arr(new_argv);
		return (0);
	}
	return (new_argv);
}
