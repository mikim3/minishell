/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/23 20:56:03 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	main_init()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);  //  시그널 ^C 출력안되게 설장하기
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// set_signal(SHE, SHE); // 시그널
	g_exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*token_list;
	char		*input;
	t_tree_node	*token_tree;
	t_detower	*dll_envp_tower;
	char		**mnsh_envp;
	// struct termios		term;

	// 터미널제어 함수 
	// tcgetattr(STDIN_FILENO, &term);

	// main_init();
	if (argc >= 2 || argv[1] != 0)
		return (FT_ERROR);
	dll_envp_tower = ft_set_envp_dll(envp);
	if (dll_envp_tower == 0)
		return (FT_ERROR);
	mnsh_envp = ft_set_char_envp_from_dll(dll_envp_tower, 0);
	// int i = -1;
	// while (mnsh_envp[++i])
	// 	printf("%s\n",mnsh_envp[i]);
	if (mnsh_envp == 0)
		return (FT_ERROR);
		
	// envp 추가 함수 - A _ a 순서에 맞게 배열하는 함수 -> 실행부에 넘김
	// envp 제거 함수???? -> 실행부에 넘김
	while (1)
	{
		input = readline("minishell$ ");
		if (*input != '\0')
			add_history(input);
		token_list = (t_list *)ft_tokenizer(input);
		if (token_list != 0)
		{
			if (ft_syntax_analysis(token_list) == FT_SUCCESS)
			{
				token_tree = ft_syntax_parse_tree(token_list);
				if (token_tree != 0)
				{
					//작업 임시 테스트
					test_print_token_lst(token_list);
					ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);


					ft_tree_node_pre_traversal(token_tree, &test_tree_node_check_for_content);
					ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
				}
			}
		}
		// tcsetattr(STDIN_FILENO, TCSANOW, &term);
		system("leaks minishell | grep LEAK");
	}
	return (FT_SUCCESS);
}

