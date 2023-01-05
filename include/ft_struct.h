/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 15:52:10 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

// ft_doubly_linked_list

typedef struct s_d_list
{
	void			*content;
	struct s_d_list	*prev;
	struct s_d_list	*next;
}				t_d_list;

typedef struct s_deque_tower
{
	t_d_list	*head;
	t_d_list	*tail;
}				t_detower;

typedef struct s_envp_content{
	char	*key;
	char	*value;
}	t_env_ctnt;

// ft_pipe

typedef struct s_redirection_data
{
	int		pipe[2];
	int		infile_fd;
	int		outfile_fd;
	int		pre_pipe_read_end;
	int		pre_pipe_check;
	int		next_pipe_check;
	int		mnsh_builtin;
	int		in_redirected;
	int		out_redirected;
	int		here_doc_opened;
}		t_pipe;

// ft_token_expansion

typedef struct s_token{
	char	*str;
	int		type;
	int		expandable;
}		t_tkn;

typedef struct s_tokenizer_data{
	t_list	*tkn_list;
	t_tkn	*tkn;
	char	*str_pos;
	char	*tkn_start;
	int		tkn_len;
	int		io_num_mode;
	int		oper_len;
	int		expandable;
}		t_tknizer;

// ft_tree

typedef struct s_minishell_tree_node{
	int								type;
	void							*content;
	struct s_minishell_tree_node	*left;
	struct s_minishell_tree_node	*right;
}	t_tree_node;

typedef struct s_minishell_tree_node_redir{
	char	*redir;
	char	*file_name;
}	t_tree_rdr;

typedef struct s_minishell_tree_node_cmd{
	char	*cmd_name;
	char	**cmd_argv;
}	t_tree_cmd;

#endif