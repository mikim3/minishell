/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:37:05 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 14:36:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H

# include "../libft/libft.h"

typedef struct s_tree_node{
	void		*content;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_minishell_tree_redir_content{
	int		type;
	char	*file;
}	t_mnsh_tree_redir;

typedef struct s_minishell_tree_cmd_content{
	char	*cmd;
	char	**cmd_argv;
}	t_mnsh_tree_cmd;

t_tree_node	*ft_syntax_parse_tree(t_list *token_list);

#endif