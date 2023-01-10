/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:35:39 by kshim             #+#    #+#             */
/*   Updated: 2023/01/10 14:18:24 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main_check_pipeline(t_parser *parser, \
	t_detower *dll_envp_tower)
{
	t_tree_node	*prev_pipeline;
	t_tree_node	*pipeline;

	pipeline = parser->token_tree;
	while (pipeline != 0)
	{
		if (main_check_pipeline_loop(&pipeline, &prev_pipeline, \
			parser, dll_envp_tower) == FT_ERROR)
			return (FT_ERROR);
		prev_pipeline = pipeline;
		pipeline = pipeline->right;
	}
	add_history(parser->org_cpy);
	return (FT_SUCCESS);
}

int	main_check_pipeline_loop(t_tree_node **pipeline, \
	t_tree_node **prev_pipeline, \
	t_parser *parser, t_detower *dll_envp_tower)
{
	char	*input;

	if ((*pipeline) != parser->token_tree && \
		(*pipeline)->left->left->left == 0 && \
		(*pipeline)->left->right->content == 0)
	{
		(*prev_pipeline)->right = 0;
		if (main_check_pipeline_readline(\
			&input, &(parser->org_cpy)) == FT_ERROR)
			return (add_history(parser->org_cpy), FT_ERROR);
		ft_tree_node_post_traversal(*pipeline, \
			&ft_free_a_tree_node);
		parser->input = input;
		if (main_parser(parser, pipeline, &dll_envp_tower) == BOOL_TRUE)
			return (add_history(parser->org_cpy), free(input), FT_ERROR);
		else
			(*prev_pipeline)->right = *pipeline;
		free(input);
	}
	return (FT_SUCCESS);
}

int	main_check_pipeline_readline(char **input, char **cpy_org)
{
	char	*tmp;

	if (main_check_pipeline_readline_loop(input) == FT_ERROR)
		return (FT_ERROR);
	if (*input != 0)
	{
		tmp = ft_strjoin(*cpy_org, " ");
		if (tmp == 0)
			return (FT_ERROR);
		free(*cpy_org);
		*cpy_org = ft_strjoin(tmp, *input);
		if (*cpy_org == 0)
			return (FT_ERROR);
		free(tmp);
	}
	return (FT_SUCCESS);
}

int	main_check_pipeline_readline_loop(char **input)
{
	*input = 0;
	while (*input == 0)
	{
		*input = readline("> ");
		if (*input == NULL)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[2C", STDOUT_FILENO);
			ft_putstr_fd(\
				"BABYSHELL: syntax error: unexpected end of file\n", \
					STDERR_FILENO);
			return (FT_ERROR);
		}
		if (**input == '\0')
		{
			free(*input);
			*input = 0;
		}
	}
	return (FT_SUCCESS);
}
