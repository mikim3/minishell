/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/10 15:37:37 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_detower			*dll_envp_tower;
	struct termios		main_term;

	tcgetattr(STDIN_FILENO, &main_term);
	main_init(argc, argv);
	dll_envp_tower = ft_set_envp_dll(envp);
	if (dll_envp_tower == 0)
		return (FT_ERROR);
	while (1)
	{
		term_init();
		input = ft_readline("BABYSHELL$ ", &main_term);
		main_loop(input, dll_envp_tower, &main_term);
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
	return (input);
}

int	main_loop(char *input, t_detower *dll_envp_tower, struct termios *term)
{
	t_parser	parser;
	t_pipe		m_pipe;
	int			err;

	ft_memset(&parser, 0, sizeof(t_parser));
	m_pipe.term = term;
	parser.input = input;
	err = main_parser(&parser, &(parser.token_tree), &dll_envp_tower);
	if (err == BOOL_TRUE)
		return (add_history(parser.input), FT_ERROR);
	else
	{
		init_pipe(&m_pipe);
		parser.org_cpy = ft_strdup(input);
		if (parser.org_cpy == 0
			|| main_check_pipeline(&parser, \
				dll_envp_tower) == FT_ERROR)
			return (free(parser.org_cpy), ft_tree_node_post_traversal(\
				parser.token_tree, &ft_free_a_tree_node), FT_ERROR);
		execute_fork(parser.token_tree, dll_envp_tower, &m_pipe);
		ft_tree_node_post_traversal(parser.token_tree, \
			&ft_free_a_tree_node);
	}
	return (free(parser.org_cpy), FT_SUCCESS);
}

int	main_parser(t_parser *parser, t_tree_node **tree_node, \
	t_detower **dll_envp_tower)
{
	int	err;

	err = ft_tokenizer(parser->input, &(parser->token_list));
	if (err == BOOL_TRUE)
		return (FT_ERROR);
	if (err == BOOL_FALSE && ft_syntax_analysis(parser->token_list) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_here_doc_expansion(parser->token_list, \
		*dll_envp_tower, &(parser->pipe_num)) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_token_expansion(\
		parser->token_list, *dll_envp_tower) \
		== FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_syntax_parse_tree(\
		parser->token_list, tree_node) \
		== FT_ERROR)
		err = BOOL_TRUE;
	return (err);
}
