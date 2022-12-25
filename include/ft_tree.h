/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:37:05 by kshim             #+#    #+#             */
/*   Updated: 2022/12/25 20:21:47 by mikim3           ###   ########.fr       */
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
	NODE_REDIR,
	NODE_FD_REDIR,
}	t_mnsh_tree_node_type;

typedef struct s_minishell_tree_node{
	int		type;
	void	*content;
	struct s_minishell_tree_node	*left;
	struct s_minishell_tree_node	*right;
}	t_tree_node;

typedef struct s_minishell_tree_node_redir{
	char	*redir;
	char	*file_name;
}	t_tree_redir;

// ex) ls haha | cat hhh    --> cmd_name = ls  cmd_argv = ls, haha , cmd_name = cat cmd_argv = cat, hhhh 
typedef struct s_minishell_tree_node_cmd{
	char	*cmd_name;
	char	**cmd_argv;
}	t_tree_cmd;

t_tree_node	*ft_tree_init(int type, void *node_content);
int	ft_tree_node_pre_traversal(t_tree_node *target_tree, void (*function)(void *));
int	ft_tree_node_post_traversal(t_tree_node *target_tree, void (*function)(void *));

t_tree_node	*ft_syntax_parse_tree(t_list *token_list);
int ft_syntax_parse_pipeline(t_list *token, t_tree_node **parse);

int	ft_syntax_parse_redirections(t_list **token, t_tree_node *cur_redirects, int token_type);
t_tree_redir	*ft_node_content_redir(t_list **token);

int	ft_syntax_parse_cmd(t_list **token, t_tree_node *cmd);
char **ft_set_cmd_argv(char **argv, char *str);

void	ft_free_string_ptr_arr(char **argv);

void	ft_free_a_tree_node(void *target);

#endif