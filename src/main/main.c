/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/09 18:52:28 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_detower			*dll_envp_tower;
	struct termios		main_term;

	if (argc == 0 && argv == 0)
		return (FT_ERROR);
	tcgetattr(STDIN_FILENO, &main_term);
	main_init();
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
	t_pipe		m_pipe;
	t_list		*token_list;
	t_tree_node	*token_tree;
	int			err;
	char		*org_input;

	m_pipe.term = term;
	err = main_parser(input, &token_list, &token_tree, &dll_envp_tower);
	if (err == BOOL_TRUE)
		return (FT_ERROR);
	else
	{
		init_pipe(&m_pipe);
		org_input = ft_strdup(input);
		if (org_input == 0
			|| main_check_pipeline(&org_input, token_tree, \
				dll_envp_tower) == FT_ERROR)
			return (free(org_input), ft_tree_node_post_traversal(\
				token_tree, &ft_free_a_tree_node), FT_ERROR);
		execute_fork(token_tree, dll_envp_tower, &m_pipe);
		ft_tree_node_post_traversal(token_tree, \
			&ft_free_a_tree_node);
	}
	return (free(org_input), FT_SUCCESS);
}

int	main_parser(char *input, t_list **token_list,
	t_tree_node **token_tree, t_detower **dll_envp_tower)
{
	int	err;

	err = ft_tokenizer(input, token_list);
	if (err == BOOL_TRUE)
		return (FT_ERROR);
	if (err == BOOL_FALSE && ft_syntax_analysis(*token_list) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_here_doc_expansion(*token_list, \
		*dll_envp_tower) == FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_token_expansion(*token_list, *dll_envp_tower) \
		== FT_ERROR)
		err = BOOL_TRUE;
	if (err == BOOL_FALSE && ft_syntax_parse_tree(*token_list, token_tree) \
		== FT_ERROR)
		err = BOOL_TRUE;
	return (err);
}
