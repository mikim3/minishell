/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_parse_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:46:11 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 16:10:38 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_syntax_parse_tree(t_list *token_list, t_tree_node **parse_tree)
{
	int			status;

	if (ft_token_type(token_list) == TKN_NULL)
	{
		ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
		return (FT_ERROR);
	}
	status = ft_syntax_parse_pipeline(token_list, parse_tree);
	if (status == FT_ERROR)
	{
		ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
		ft_tree_node_post_traversal(*parse_tree, &ft_free_a_tree_node);
		return (FT_ERROR);
	}
	ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
	return (FT_SUCCESS);
}

int	ft_syntax_parse_pipeline(t_list *token, t_tree_node **parse)
{
	t_tree_node	*recur_parse;
	t_tree_node	*cur_redirects;
	t_tree_node	*simple_cmd;
	int			token_type;

	if (ft_syntax_parse_pipeline_data(parse, &recur_parse,
			&cur_redirects, &simple_cmd) == FT_ERROR)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	token_type = ft_token_type(token);
	if (ft_syntax_parse_token_traversal(&token_type, &token,
			cur_redirects, simple_cmd) == FT_ERROR)
		return (FT_ERROR);
	if (token_type == TKN_PIPE)
	{
		token = token->next;
		if (ft_syntax_parse_pipeline(token, &recur_parse) == FT_ERROR)
			return (FT_ERROR);
		(*parse)->right = recur_parse;
	}
	return (FT_SUCCESS);
}

int	ft_syntax_parse_pipeline_data(t_tree_node **parse,
	t_tree_node **recur_parse, t_tree_node **cur_redirects,
	t_tree_node **simple_cmd)
{
	*recur_parse = 0;
	*cur_redirects = 0;
	*parse = ft_tree_init(NODE_PIPELINE, 0);
	if (*parse == 0)
		return (FT_ERROR);
	*simple_cmd = ft_tree_init(NODE_SIMPLE_CMD, 0);
	if (*simple_cmd == 0)
		return (FT_ERROR);
	(*simple_cmd)->left = ft_tree_init(NODE_REDIRECTIONS, 0);
	if ((*simple_cmd)->left == 0)
		return (FT_ERROR);
	(*simple_cmd)->right = ft_tree_init(NODE_CMD, 0);
	if ((*simple_cmd)->right == 0)
		return (FT_ERROR);
	(*parse)->left = *simple_cmd;
	*cur_redirects = (*simple_cmd)->left;
	return (FT_SUCCESS);
}

int	ft_syntax_parse_token_traversal(int *token_type, t_list **token,
	t_tree_node *cur_redirects, t_tree_node *simple_cmd)
{
	while (*token_type != TKN_NULL && *token_type != TKN_PIPE)
	{
		if (*token_type == TKN_REDIRECT || *token_type == TKN_FD_REDIRECT)
		{
			if (ft_syntax_parse_redirections(token,
					cur_redirects, *token_type) == FT_ERROR)
				return (FT_ERROR);
			cur_redirects = cur_redirects->right;
		}
		else if (*token_type == TKN_WORD)
		{
			if (ft_syntax_parse_cmd(token, simple_cmd->right) == FT_ERROR)
				return (FT_ERROR);
		}
		*token = (*token)->next;
		*token_type = ft_token_type(*token);
	}
	return (FT_SUCCESS);
}

int	ft_syntax_parse_redirections(t_list **token,
	t_tree_node *cur_redirects, int token_type)
{
	if (token_type == TKN_REDIRECT)
		cur_redirects->left = ft_tree_init(NODE_REDIR, 0);
	else if (token_type == TKN_FD_REDIRECT)
		cur_redirects->left = ft_tree_init(NODE_FD_REDIR, 0);
	if (cur_redirects->left == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	cur_redirects->left->content = (void *)ft_node_content_redir(token);
	if (cur_redirects->left->content == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	cur_redirects->right = ft_tree_init(NODE_REDIRECTIONS, 0);
	if (cur_redirects->right == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	return (FT_SUCCESS);
}
