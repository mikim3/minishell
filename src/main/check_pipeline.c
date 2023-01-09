/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:35:39 by kshim             #+#    #+#             */
/*   Updated: 2023/01/09 13:52:22 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main_check_pipeline(t_tree_node *pipeline, \
	t_detower *dll_envp_tower)
{
	char		*input;
	int			err;
	t_list		*token_list;
	t_tree_node	*prev_pipeline;

	err = BOOL_FALSE;
	while (pipeline != 0)
	{
		if (pipeline->left->left->left == 0 && \
			pipeline->left->right->content == 0)
		{
			if (main_check_pipeline_readline(&input) == FT_ERROR)
				return (FT_ERROR);
			ft_tree_node_post_traversal(pipeline, \
				&ft_free_a_tree_node);
			err = main_parser(input, &token_list, &pipeline, &dll_envp_tower);
			if (err == BOOL_TRUE)
				return (FT_ERROR);
			else
				prev_pipeline->right = pipeline;
		}
		prev_pipeline = pipeline;
		pipeline = pipeline->right;
	}
	return (FT_SUCCESS);
}

int	main_check_pipeline_readline(char **input)
{
	*input = readline("> ");
	if (*input == NULL)
		return (ft_putstr_fd("BABYSHELL: syntax error: unexpected end of file", \
			STDERR_FILENO), FT_ERROR);
	if (**input != '\0')
	{
		// 
		// 이전 히스토리 tmp_prev 
	}	// add_history(input); // 기존 history 문자열에 덧붙이게 만들어야 함
	return (FT_SUCCESS);
}
