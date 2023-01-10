/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:49:10 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/10 14:46:23 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	execute_cmd(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (is_built_in(token_tree->content))
		execute_builtin(token_tree->content, dll_envp_tower, m_pipe);
	else
		execute_external(token_tree, dll_envp_tower);
}

int	is_built_in(t_tree_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	if (!ft_strcmp(cmd->cmd_name, "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "env"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "export"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "echo"))
		return (1);
	if (!ft_strcmp(cmd->cmd_name, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_tree_cmd *cmd, \
	t_detower *dll_envp_tower, t_pipe *m_pipe)
{
	if (!ft_strcmp(cmd->cmd_name, "echo"))
		ft_echo(cmd, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "cd"))
		ft_cd(cmd, dll_envp_tower);
	if (!ft_strcmp(cmd->cmd_name, "pwd"))
		ft_pwd(m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "export"))
		ft_export(cmd, dll_envp_tower, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "unset"))
		ft_unset(cmd, dll_envp_tower);
	if (!ft_strcmp(cmd->cmd_name, "env"))
		ft_env(dll_envp_tower, m_pipe);
	if (!ft_strcmp(cmd->cmd_name, "exit"))
		ft_exit(cmd, m_pipe);
	return ;
}

void	execute_external(t_tree_node *node, \
	t_detower *dll_envp_tower)
{
	char			*file_path;
	char			**env;

	file_path = set_file_path(((t_tree_cmd *)node->content)->cmd_name,
			dll_envp_tower);
	env = ft_set_char_envp_from_dll(dll_envp_tower, 0);
	ft_execve(file_path, ((t_tree_cmd *)node->content)->cmd_argv, env);
	if (!file_path)
		free(file_path);
	ft_free_string_ptr_arr(env);
}
