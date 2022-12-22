/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:01:52 by kshim             #+#    #+#             */
/*   Updated: 2022/12/22 16:07:20 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "../include/ft_tree.h"
#include "../include/ft_tokenizer.h"

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
		exit(1);
	while (*(tknizer.str_pos) != '\0')
	{
		error = ft_tokenizing_loop(&tknizer, error, &prev_type);
		if (error == BOOL_TRUE)
			exit(1);
	}
	if (ft_token_processor(&tknizer, &prev_type) == FT_ERROR)
		exit(1);
	return ((void *)(tknizer.tkn_list));
}

int	ft_initialize_tokenizer( t_tknizer *tknizer, char *str)
{
	tknizer->tkn_list = 0;
	tknizer->tkn = ft_new_token();
	if (tknizer->tkn == 0)
		return (FT_ERROR);
	tknizer->str_pos = str;
	tknizer->tkn_start = str;
	tknizer->tkn_len = 0;
	tknizer->oper_len = 0;
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
	tknizer->tkn_len++;
	tknizer->str_pos++;
	*prev_type = TKN_WORD;
	return (FT_SUCCESS);
}

int	main(void)
{
	t_list		*token_list;
	char		*input;
	t_tree_node	*token_tree;

	while (1)
	{
		input = readline("minishell$ ");
		token_list = (t_list *)ft_tokenizer(input);
		if (ft_syntax_analysis(token_list) == FT_SUCCESS)
			token_tree = ft_syntax_parse_tree(token_list);

			// token_tree 해제 타이밍은?
		// test
		test_print_token_lst(token_list);
		ft_tree_node_pre_traversal(token_tree, &test_tree_node_check_for_content);
		
		// token_list 해제
		ft_lstclear(&token_list, &ft_free_a_token_list_content);
		// token_tree 해제
		ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
		system("leaks minishell");
	}
	return (0);
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
