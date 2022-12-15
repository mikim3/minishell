/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:04:24 by kshim             #+#    #+#             */
/*   Updated: 2022/12/15 13:44:24 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKENIZER_H
# define FT_TOKENIZER_H

# include "../libft/libft.h"

typedef enum e_token_type{
	TKN_TYPE_NULL = 0,
	TKN_TYPE_WORD,
	TKN_TYPE_OPERATOR,
	TKN_TYPE_PIPE,
	TKN_TYPE_REDIRECT
}		t_tkn_type;

typedef enum e_mode_on_off{
	MODE_OFF = 0,
	MODE_ON
}		t_on_off;

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
	int		tkn_len;
	char	*tkn_start;
}		t_tknizer;

void	*ft_tokenizer(char *str);
int		ft_token_processor(t_tknizer *tknizer, char *str,
			int *prev_type, int tkn_type);
int		ft_token_set(t_tkn *token, char *token_start, int token_len);
t_tkn	*ft_token_cut(t_list **token_list, t_tkn *token);
t_tkn	*ft_new_token(void);
void	ft_token_start_set(t_tknizer *tknizer, char *str);
int		ft_can_become_operator(char diff_target, char cha, int token_len);
int		ft_is_operator(char cha);

void	test_print_token_lst(t_list *token_list);

#endif