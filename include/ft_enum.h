/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enum.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 15:52:10 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENUM_H
# define FT_ENUM_H

// pipe

typedef enum e_pipe_end_name{
	P_READ = 0,
	P_WRITE
}	t_pipe_tag;

// ft_doubly_linked_list

typedef enum e_expansion_mode{
	EXPAND_ALL = 0,
	EXPAND_QUOTE_ONLY,
	EXPAND_ENV_ONLY,
	EXPAND_D_QUOTE_WITH_ENV,
	EXPAND_D_QUOTE_WITHOUT_ENV,
	EXPAND_NOT
}	t_expand_mode;

typedef enum e_pwd_set{
	PWD_SET = 0,
	OLDPWD_SET
}		t_pwd_set;

typedef enum e_signal{
	SIG_IGNORE = 0,
	SIG_DEFAULT,
	SIG_HANDLER,
	SIG_HERE_DOC
}		t_signal;

// ft_token_expansion

typedef enum e_token_type{
	TKN_NULL = 0,
	TKN_WORD,
	TKN_OPERATOR,
	TKN_PIPE,
	TKN_REDIRECT,
	TKN_FD_REDIRECT
}		t_tkn_type;

typedef enum e_boolean{
	BOOL_FALSE = 0,
	BOOL_TRUE
}		t_boolean;

typedef enum e_error{
	FT_SUCCESS = 0,
	FT_ERROR
}		t_error;

typedef enum e_tknizer_error_state{
	TKN_TKNIZE_FAIL = 0,
	TKN_TKNIZE_SUCCESSED
}		t_tknizer_error;

// ft_tree

typedef enum e_parse_tree_node_type{
	NODE_PIPELINE = 0,
	NODE_SIMPLE_CMD,
	NODE_REDIRECTIONS,
	NODE_CMD,
	NODE_REDIR,
	NODE_FD_REDIR,
}	t_mnsh_tree_node_type;

#endif