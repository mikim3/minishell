/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 14:58:00 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	init_pipe(t_pipe *m_pipe)
{
	m_pipe->next_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_read_end = -1;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	m_pipe->mnsh_builtin = BOOL_FALSE;
	m_pipe->in_redirected = BOOL_FALSE;
	m_pipe->out_redirected = BOOL_FALSE;
	m_pipe->here_doc_opened = BOOL_FALSE;
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SIG_HANDLER, SIG_IGNORE);
	g_exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list				*token_list;
	char				*input;
	t_tree_node			*token_tree;
	t_detower			*dll_envp_tower;
	struct termios		main_term;

	tcgetattr(STDIN_FILENO, &main_term);
	main_init(argc, argv);
	dll_envp_tower = ft_set_envp_dll(envp);
	if (dll_envp_tower == 0)
		return (FT_ERROR);
	while (1)
	{
		input = ft_readline("BABYSHELL$ ");
		token_list = (t_list *)ft_tokenizer(input);
		main_loop(token_list, dll_envp_tower, token_tree);
		free(input);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &main_term);
	return (FT_SUCCESS);
}

char	*ft_readline(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		printf("see you later \n");
		exit(g_exit_code);
	}
	if (*input != '\0')
		add_history(input);
	return (input);
}

void	main_loop(t_list *token_list, t_detower *dll_envp_tower, \
	t_tree_node *token_tree)
{
	t_pipe	m_pipe;

	if (token_list != 0)
	{
		if (ft_syntax_analysis(token_list) == FT_SUCCESS)
		{
			if (ft_here_doc_expansion(token_list, dll_envp_tower) == FT_SUCCESS)
			{
				if (ft_token_expansion(token_list, dll_envp_tower) \
					== FT_SUCCESS)
				{
					token_tree = ft_syntax_parse_tree(token_list);
					if (token_tree != 0)
					{
						init_pipe(&m_pipe);
						ft_free_tokenizer_list_and_token(&token_list, \
							0, TKN_TKNIZE_SUCCESSED);
						execute_fork(token_tree, dll_envp_tower, &m_pipe);
						ft_tree_node_post_traversal(token_tree, \
							&ft_free_a_tree_node);
					}
				}
			}
		}
	}
}
