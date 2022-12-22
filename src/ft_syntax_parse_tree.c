/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_parse_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:46:11 by kshim             #+#    #+#             */
/*   Updated: 2022/12/22 15:56:43 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tree.h"
#include "../include/ft_tokenizer.h"

////
#include <stdio.h>

t_tree_node	*ft_syntax_parse_tree(t_list *token_list)
{
	t_tree_node *parse_tree;
	int			status;

	if (ft_token_what_type(token_list) == TKN_NULL)
		return (0 /* 빈 pipeline 만들어서 반환 - 0 반환하면 예외처리 힘듬 */);
	status = ft_syntax_parse_pipeline(token_list, &parse_tree);
	if (status == FT_ERROR)
	{
		printf("parse tree fail\n");
		// 해제 작업
		return (0);
	}
	printf("parse tree done\n");
	// token_list 해제 - 밖에서 처리하는게 나을까?
	return (parse_tree);
}

int ft_syntax_parse_pipeline(t_list *token, t_tree_node **parse)
{
	t_tree_node *recur_parse;
	t_tree_node *cur_redirects;
	t_tree_node	*simple_cmd;
	int			token_type;

	recur_parse = 0;
	cur_redirects = 0;
	*parse = ft_tree_init(NODE_PIPELINE, 0);
	if (*parse == 0)
		return (0);
	simple_cmd = ft_tree_init(NODE_SIMPLE_CMD, 0);
	if (simple_cmd == 0)
		return (0);
	simple_cmd->left = ft_tree_init(NODE_REDIRECTIONS, 0);
	if (simple_cmd->left == 0)
		return (0);
	simple_cmd->right = ft_tree_init(NODE_CMD, 0);
	if (simple_cmd->right == 0)
		return (0);
	(*parse)->left = simple_cmd;
	cur_redirects = simple_cmd->left;
	token_type = ft_token_what_type(token);
	while (token_type != TKN_NULL && token_type != TKN_PIPE)
	{
		if (token_type == TKN_REDIRECT || token_type == TKN_FD_REDIRECT)
		{
			if (ft_syntax_parse_redirections(&token, cur_redirects, token_type) == FT_ERROR)
			{
				// tree 해제
				return (FT_ERROR);
			}
			cur_redirects = cur_redirects->right;
		}
		else if (token_type == TKN_WORD)
		{
			if (ft_syntax_parse_cmd(&token, simple_cmd->right) == FT_ERROR)
			{
				// tree 해제
				return (FT_ERROR);
			}
		}
		token = token->next;
		token_type = ft_token_what_type(token);
	}
	if (token_type == TKN_PIPE)
	{
		token = token->next;
		if (ft_syntax_parse_pipeline(token, &recur_parse) == FT_ERROR)
		{
			// tree 해제
			return (FT_ERROR);
		}
		(*parse)->right = recur_parse;
	}
	return (FT_SUCCESS);
}

int	ft_syntax_parse_redirections(t_list **token, t_tree_node *cur_redirects, int token_type)
{

	if (token_type == TKN_REDIRECT)
		cur_redirects->left = ft_tree_init(NODE_REDIR, 0);
	else if (token_type == TKN_FD_REDIRECT)
		cur_redirects->left = ft_tree_init(NODE_FD_REDIR, 0);
	if (cur_redirects->left == 0)
		return (FT_ERROR);
	cur_redirects->left->content = (void *)ft_node_content_redir(token);
	if (cur_redirects->left->content == 0)
		return (FT_ERROR);
	cur_redirects->right = ft_tree_init(NODE_REDIRECTIONS, 0);
	if (cur_redirects->right == 0)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

t_tree_redir	*ft_node_content_redir(t_list **token)
{
	t_tree_redir	*redir_node;

	redir_node = (t_tree_redir *)malloc(sizeof(t_tree_redir));
	if (redir_node == 0)
		return (0);
	redir_node->redir = ft_strdup(ft_token_what_str(*token));
	if (redir_node->redir == 0)
		return (0);
	*token = (*token)->next;
	redir_node->file_name = ft_strdup(ft_token_what_str(*token));
	if (redir_node->file_name == 0)
		return (0);
	return (redir_node);
}

int	ft_syntax_parse_cmd(t_list **token, t_tree_node *cmd)
{
	if (cmd->content == 0)
	{
		cmd->content = (t_tree_cmd *)malloc(sizeof(t_tree_cmd));
		if (cmd->content == 0)
			return (FT_ERROR);
		((t_tree_cmd *)(cmd->content))->cmd_name = ft_strdup(ft_token_what_str(*token));
		if (((t_tree_cmd *)(cmd->content))->cmd_name == 0)
			return (FT_ERROR);
		((t_tree_cmd *)(cmd->content))->cmd_argv = 0;
	}
	((t_tree_cmd *)(cmd->content))->cmd_argv = ft_set_cmd_argv(((t_tree_cmd *)(cmd->content))->cmd_argv, ft_token_what_str(*token));
	if (((t_tree_cmd *)(cmd->content))->cmd_argv == 0)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

char **ft_set_cmd_argv(char **argv, char *str)
{
	int		argv_size;
	char	**new_argv;
	int		i;

	argv_size = 1;
	if (argv != 0)
	{
		while (argv[argv_size - 1] != 0)
			argv_size++;
	}
	new_argv = ft_calloc((argv_size + 1), sizeof(char *));
	if (new_argv == 0)
		return (0);
	new_argv[argv_size] = 0;
	new_argv[argv_size - 1] = ft_strdup(str);
	if (new_argv[argv_size - 1] == 0)
	{
		ft_free_parse_argv(new_argv);
		return (0);
	}
	if (argv == 0)
		return (new_argv);
	i = 0;
	while (argv[i] != 0)
	{
		new_argv[i] = ft_strdup(argv[i]);
		if (new_argv[i] == 0)
		{
			ft_free_parse_argv(new_argv);
			return (0);
		}
		i++;
	}
	ft_free_parse_argv(argv);
	return (new_argv);
}

void	ft_free_parse_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != 0)
	{
		free(argv[i]);
		argv[i] = 0;
		i++;
	}
	free(argv);
	return ;	
}
