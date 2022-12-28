/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:01:52 by kshim             #+#    #+#             */
/*   Updated: 2022/12/28 16:49:53 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "../../include/ft_tree.h"
#include "../../include/ft_tokenizer.h"
#include "../../include/ft_doubly_linked_list.h"
#include "../../include/ft_token_expansion.h"

// 예외처리를 임시로 exit로 해둠. exit 사용을 위한 헤더
#include <stdlib.h>
#include <unistd.h>

void	*ft_tokenizer(char *str)
{
	t_tknizer	tknizer;
	int			prev_type;
	int			error;
	// 코드 밖 코멘트, 사용하지 않을 헤더 존재함
	prev_type = TKN_WORD;
	error = BOOL_FALSE;
	if (ft_initialize_tokenizer(&tknizer, str) == FT_ERROR)
		return (0);
	while (*(tknizer.str_pos) != '\0')
	{
		error = ft_tokenizing_loop(&tknizer, error, &prev_type);
		if (error == BOOL_TRUE)
		{
			ft_free_tokenizer_list_and_token(&(tknizer.tkn_list), &(tknizer.tkn), TKN_TKNIZE_FAIL);
			return (0);
		}
	}
	if (ft_token_processor(&tknizer, &prev_type) == FT_ERROR)
	{
		ft_free_tokenizer_list_and_token(&(tknizer.tkn_list), &(tknizer.tkn), TKN_TKNIZE_FAIL);
		return (0);
	}
	return ((void *)(tknizer.tkn_list));
}

int	ft_initialize_tokenizer(t_tknizer *tknizer, char *str)
{
	tknizer->tkn_list = 0;
	tknizer->tkn = ft_new_token();
	if (tknizer->tkn == 0)
		return (FT_ERROR);
	tknizer->str_pos = str;
	tknizer->tkn_start = str;
	tknizer->tkn_len = 0;
	tknizer->oper_len = 0;
	tknizer->expandable = BOOL_FALSE;
	if (ft_isdigit(*str) == BOOL_TRUE)
		tknizer->io_num_mode = BOOL_TRUE;
	else
		tknizer->io_num_mode = BOOL_FALSE;
	return (FT_SUCCESS);
}

int	ft_tokenizing_loop(t_tknizer *tknizer, int error, int *prev_type)
{
	if (ft_is_quote(*(tknizer->str_pos)) == BOOL_TRUE)
		error = ft_close_quote(tknizer, prev_type);
	if (*(tknizer->str_pos) == '$')
		tknizer->expandable = BOOL_TRUE;
	if (error == BOOL_FALSE && *prev_type == TKN_OPERATOR)
	{
		if (tknizer->oper_len == 1
			|| ft_can_become_operator(*(tknizer->str_pos - 1),
				*(tknizer->str_pos), &(tknizer->oper_len)) == BOOL_FALSE)
			error = ft_token_processor(tknizer, prev_type);
	}
	if (error == BOOL_FALSE && *prev_type != TKN_OPERATOR
		&& ft_is_operator(*(tknizer->str_pos)) == BOOL_TRUE)
	{
		if (tknizer->io_num_mode == BOOL_TRUE)
			*prev_type = TKN_OPERATOR;
		else
			error = ft_token_processor(tknizer, prev_type);
	}
	if (error == BOOL_FALSE
		&& ft_isspace(*(tknizer->str_pos)) == BOOL_TRUE)
		error = ft_token_processor(tknizer, prev_type);
	else
	{
		if (*prev_type != TKN_OPERATOR
			&& ft_isdigit(*(tknizer->str_pos)) == BOOL_FALSE)
			tknizer->io_num_mode = BOOL_FALSE;
		tknizer->str_pos++;
		tknizer->tkn_len++;
	}
	return (error);
}

int	ft_close_quote(t_tknizer *tknizer, int *prev_type)
{
	char	target;
	// 형태 마음에 안든다. 반복 조건 조정해서 리팩토링.
	if (*prev_type == TKN_OPERATOR
		&& ft_token_processor(tknizer, prev_type) == FT_ERROR)
		return (FT_ERROR);
	target = *(tknizer->str_pos);
	tknizer->tkn_len++;
	tknizer->str_pos++;
	while (*(tknizer->str_pos) != target)
	{
		if (*(tknizer->str_pos) == '\0')
			return (FT_ERROR);
		tknizer->tkn_len++;
		tknizer->str_pos++;
	}
	if (*(tknizer->str_pos) == '\0')
		return (FT_ERROR);
	tknizer->io_num_mode = BOOL_FALSE;
	tknizer->expandable = BOOL_TRUE;
	//tknizer->tkn_len++;
	//tknizer->str_pos++;
	*prev_type = TKN_WORD;
	return (FT_SUCCESS);
}



void	test_print_token_lst(t_list *token_list)
{
	int		i;
	char	*type[6] = {"NULL", "WORD", "OPERATOR", "PIPE", "REDIRECT", "FD_REDIRECT"};

	i = 1;
	while (token_list != 0)
	{
		printf("token %d : %s, ", i, ((t_tkn *)token_list->content)->str);
		printf("type %s\n", type[((t_tkn *)token_list->content)->type]);
		token_list = token_list->next;
		i++;
	}
	return ;
}

void	test_tree_node_check_for_content(void *tree_node)
{
	t_tree_node *node;
	int	i;

	i = 0;
	node = (t_tree_node *)tree_node;
	if (node->type == NODE_CMD)
	{
		if (node->content == 0)
			return ;
		printf("node_cmd_name : %s\n", ((t_tree_cmd *)node->content)->cmd_name);
		while (((t_tree_cmd *)node->content)->cmd_argv[i] != 0)
		{
			printf("node_cmd_argv : %s\n", ((t_tree_cmd *)node->content)->cmd_argv[i]);
			i++;
		}
		printf("\n");
	}
	else if (node->type == NODE_REDIR
		|| node->type == NODE_FD_REDIR)
	{
		if (node -> content == 0)
			return ;
		printf("node_redir : %s\n", ((t_tree_redir *)node->content)->redir);
		printf("node_file_name : %s\n", ((t_tree_redir *)node->content)->file_name);
	}
	return ;
}

void	test_print_dll_envp(t_detower *dll)
{
	t_d_list		*node;
	
	node = dll->head;
	printf("dll_envp\n\n");
	while (node != 0)
	{
		printf("%s\n",((t_envp_content *)node->content)->key);
		node = node->next;
	}
	printf("\n");
}

void	test_print_mnsh_envp(char **mnsh_envp)
{
	int	iter;

	iter = 0;
	printf("mnsh_envp\n\n");
	while (mnsh_envp[iter] != 0)
	{
		printf("%s\n", mnsh_envp[iter]);
		iter++;
	}
	printf("\n");
	return ;
}
