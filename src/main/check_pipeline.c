/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:35:39 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 18:52:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main_check_pipeline(char **org_cpy, t_tree_node *pipeline, \
	t_detower *dll_envp_tower)
{
	char		*input;
	t_list		*token_list;
	t_tree_node	*prev_pipeline;

	while (pipeline != 0)
	{
		if (pipeline->left->left->left == 0 && \
			pipeline->left->right->content == 0)
		{
			if (main_check_pipeline_readline(&input, org_cpy) == FT_ERROR)
				return (FT_ERROR);
			ft_tree_node_post_traversal(pipeline, \
				&ft_free_a_tree_node);
			if (main_parser(input, &token_list, \
				&pipeline, &dll_envp_tower) == BOOL_TRUE)
				return (free(input), FT_ERROR);
			else
				prev_pipeline->right = pipeline;
			free(input);
		}
		prev_pipeline = pipeline;
		pipeline = pipeline->right;
	}
	add_history(*org_cpy);
	return (FT_SUCCESS);
}

int	main_check_pipeline_readline(char **input, char **cpy_org)
{
	char	*tmp;
	char	*without_prom;

	if (main_check_pipeline_readline_loop(input) == FT_ERROR)
		return (FT_ERROR);
	if (*input != 0)
	{
		without_prom = *input + 2;
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
