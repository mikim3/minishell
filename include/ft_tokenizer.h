/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:04:24 by kshim             #+#    #+#             */
/*   Updated: 2022/12/19 14:28:25 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKENIZER_H
# define FT_TOKENIZER_H

# include "../libft/libft.h"

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

typedef struct s_token{
	char	*str;
	int		type;
}		t_tkn;

typedef struct s_tokenizer_data{
	t_list	*tkn_list;
	t_tkn	*tkn;
	char	*str_pos;
	char	*tkn_start;
	int		tkn_len;
	int		io_num_mode;
	int		oper_len;
}		t_tknizer;

void	*ft_tokenizer(char *str);
int		ft_initialize_tokenizer( t_tknizer *tknizer, char *str);
int		ft_tokenizing_loop(t_tknizer *tknizer, int error, int *prev_type);
int		ft_close_quote(t_tknizer *tknizer, int *prev_type);

int		ft_token_processor(t_tknizer *tknizer,
			int *prev_type);
int		ft_token_set(t_tknizer *tknizer, int type);
int		ft_token_cut(t_list **token_list, t_tkn *token);
t_tkn	*ft_new_token(void);
void	ft_token_start_set(t_tknizer *tknizer);

int		ft_is_quote(char cha);
int		ft_can_become_operator(char diff_target, char cha, int *oper_len);
int		ft_is_operator(char cha);

void	test_print_token_lst(t_list *token_list);

int	ft_syntax_analysis(t_list *token_list);

int	ft_stx_a_pipeline(t_list *token_pos);
int ft_stx_a_simple_cmd(t_list *token_pos);
int ft_stx_a_cmd_prefix(t_list *token_pos);
int ft_stx_a_cmd_suffix(t_list *token_pos);
int ft_stx_a_io_redir(t_list *token_pos);

int ft_stx_a_redir(t_list *token_pos);
int	ft_stx_a_word(t_list *token_pos);

#endif