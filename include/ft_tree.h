/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:37:05 by kshim             #+#    #+#             */
/*   Updated: 2022/12/19 11:21:59 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H

typedef struct s_tree_node{
	void		*content;
	t_tree_node	*left;
	t_tree_node	*right;
}	t_tree_node;

typedef struct s_minishell_tree_content{
	char 	*str;
	int		type;
}	t_mnsh_content;

#endif