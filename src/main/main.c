/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/09 12:54:57 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list				*token_list;
	char				*input;
	t_tree_node			*token_tree;
	t_detower			*dll_envp_tower;
	struct termios		main_term;

	if (argc == 0 && argv == 0)
		return (FT_ERROR);
	tcgetattr(STDIN_FILENO, &main_term);
	main_init();
	dll_envp_tower = ft_set_envp_dll(envp);
	if (dll_envp_tower == 0)
		return (FT_ERROR);
	token_tree = 0;
	while (1)
	{
		term_init();
		input = ft_readline("BABYSHELL$ ", &main_term);
		token_list = (t_list *)ft_tokenizer(input);
		main_loop(token_list, dll_envp_tower, token_tree, &main_term);
		free(input);
		tcsetattr(STDIN_FILENO, TCSANOW, &main_term);
	}
	return (FT_SUCCESS);
}

char	*ft_readline(char *prompt, struct termios *main_term)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		ft_putstr_fd("see you later \n", STDOUT_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, main_term);
		exit(g_exit_code);
	}
	if (*input != '\0')
		add_history(input);
	return (input);
}

void	main_loop(t_list *token_list, t_detower *dll_envp_tower, \
	t_tree_node *token_tree, struct termios *term)
{
	t_pipe	m_pipe;
	int		err;

	err = BOOL_FALSE;
	m_pipe.term = term;
	err = main_parser(&token_list, &dll_envp_tower);
	if (err == BOOL_FALSE)
	{
		token_tree = ft_syntax_parse_tree(token_list);
		if (token_tree == 0)
			err = BOOL_TRUE;
		else
		{
			ft_free_tokenizer_list_and_token(&token_list, \
				0, TKN_TKNIZE_SUCCESSED);
			init_pipe(&m_pipe);
			if (main_check_pipeline(token_tree, dll_envp_tower) == FT_ERROR)
			{
				ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
				return ;
			}
			execute_fork(token_tree, dll_envp_tower, &m_pipe);
			ft_tree_node_post_traversal(token_tree, \
				&ft_free_a_tree_node);
		}
	}
}

int	main_parser(t_list **token_list, t_detower **dll_envp_tower)
{
	int	err;

	err = BOOL_FALSE;
	if (token_list == 0)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_syntax_analysis(*token_list) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_here_doc_expansion(*token_list, \
		*dll_envp_tower) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_token_expansion(*token_list, *dll_envp_tower) \
		== FT_ERROR)
		err = BOOL_TRUE;
	return (err);
}

int	main_check_pipeline(t_tree_node *pipeline, \
	t_detower *dll_envp_tower)
{
	char		*input;
	int			err;
	t_list		*token_list;
	t_tree_node	*prev_pipeline;

	err = BOOL_FALSE;
	prev_pipeline = 0;
	while (pipeline != 0)
	{
		if (pipeline->left->left->left == 0 && \
			pipeline->left->right->content == 0)
		{
			if (main_check_pipeline_readline(&input) == FT_ERROR)
				return (FT_ERROR);
			ft_tree_node_post_traversal(pipeline, \
				&ft_free_a_tree_node);
			token_list = (t_list *)ft_tokenizer(input);
			err = main_parser(&token_list, &dll_envp_tower);
			if (err == BOOL_FALSE)
			{
				pipeline = ft_syntax_parse_tree(token_list);
				if (pipeline == 0)
					return (ft_free_tokenizer_list_and_token(&token_list, \
						0, TKN_TKNIZE_SUCCESSED), FT_ERROR);
				else
				{
					ft_free_tokenizer_list_and_token(&token_list, \
						0, TKN_TKNIZE_SUCCESSED);
					prev_pipeline->right = pipeline;
				}
			}
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
		
	}	// add_history(input); // 기존 history 문자열에 덧붙이게 만들어야 함
	return (FT_SUCCESS);
}
