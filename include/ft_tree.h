/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:37:05 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 14:42:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H

# include "../libft/libft.h"

typedef enum e_parse_tree_node_type{
	NODE_PIPELINE = 0,
	NODE_SIMPLE_CMD,
	NODE_REDIRECTIONS,
	NODE_CMD,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR,
	NODE_CMD_NAME,
	NODE_CMD_ARGV
}	t_mnsh_tree_node_type;

typedef struct s_tree_node{
	void		*content;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_minishell_tree_redir_content{
	int		node_type;
	char	*file;
}	t_mnsh_tree_redir;

typedef struct s_minishell_tree_cmd_content{
	int		node_type;
	char	*cmd;
	char	**cmd_argv;
}	t_mnsh_tree_cmd;

t_tree_node	*ft_syntax_parse_tree(t_list *token_list);

#endif