/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/31 14:43:21 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	init_pipe(t_pipe *m_pipe)
{
	m_pipe->next_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_read_end = -1;
//	m_pipe->pipe_write_end = STDOUT_FILENO;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SIG_HANDLER,SIG_IGNORE);
	g_exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*token_list;
	char		*input;
	t_tree_node	*token_tree;
	t_detower	*dll_envp_tower;
	char		**mnsh_envp;
	t_pipe		m_pipe;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(argc, argv);
	if (argc >= 2 || argv[1] != 0)
		print_err_exit("'babyshell' only accepts one arg", FT_ERROR);
	dll_envp_tower = ft_set_envp_dll(envp);
	if (dll_envp_tower == 0)
		return (FT_ERROR);
	mnsh_envp = ft_set_char_envp_from_dll(dll_envp_tower, 0);
	if (mnsh_envp == 0)
		return (FT_ERROR);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL) //  Ctrl + D를 누르면 input은 NULL이 들어옴
		{
			printf("see you later \n");
			return (FT_SUCCESS);
		}
		if (*input != '\0')
			add_history(input);
		token_list = (t_list *)ft_tokenizer(input);
		if (token_list != 0)
		{
			if (ft_syntax_analysis(token_list) == FT_SUCCESS)
			{
				// 문맥 분석 완료한 경우 here_doc 작성 - delimiter의 특징 때문에 확장보다 우선함
				if (ft_here_doc_expansion(token_list, dll_envp_tower) == FT_SUCCESS)
				{
					// 성공한 경우에만 환경 변수 확장
					if (ft_token_expansion(token_list, dll_envp_tower) == FT_SUCCESS)
					{
						token_tree = ft_syntax_parse_tree(token_list);
						if (token_tree != 0)
						{
							//작업 임시 테스트
							test_print_token_lst(token_list);
							init_pipe(&m_pipe);
							
							ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
							// ft_execute_tree(token_tree,dll_envp_tower, &m_pipe);
							ft_tree_node_pre_traversal(token_tree, &test_tree_node_check_for_content);
							
							// 실행용
							//ft_tree_node_pre_traversal2(token_tree, dll_envp_tower, &m_pipe, &ft_execute_tree);
							execute_fork(token_tree, dll_envp_tower, &m_pipe);
							// ft_tree_node_pre_traversal(token_tree, &ft_execute_tree_node);

							// tree 해제
							ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
						}
					}
				}
	
			}
		}
		// tcsetattr(STDIN_FILENO, TCSANOW, &term);
		free(input);
		system("leaks minishell | grep LEAK");
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	return (FT_SUCCESS);
}

int	ft_tree_node_pre_traversal2(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe, void (*function)(t_tree_node *,t_detower *,t_pipe *))
{
	if (token_tree == BOOL_FALSE)
		return (FT_ERROR);
	if ((*function) == BOOL_FALSE)
		return (FT_ERROR);
	function((t_tree_node *)token_tree,(t_detower *)dll_envp_tower,(t_pipe *)m_pipe);
	ft_tree_node_pre_traversal2(token_tree->left, dll_envp_tower, m_pipe, (*function));
	ft_tree_node_pre_traversal2(token_tree->right, dll_envp_tower, m_pipe, (*function));
	return (FT_SUCCESS);
}

// ///

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list		*token_list;
// 	char		*input;
// 	t_tree_node	*token_tree;
// 	t_detower	*dll_envp_tower;
// 	char		**mnsh_envp;

// 	if (argc >= 2 || argv[1] != 0)
// 		return (FT_ERROR);
// 	dll_envp_tower = ft_set_envp_dll(envp);
// 	if (dll_envp_tower == 0)
// 		return (FT_ERROR);
// 	mnsh_envp = ft_set_char_envp_from_dll(dll_envp_tower, 0);
// 	if (mnsh_envp == 0)
// 		return (FT_ERROR);
// 	// envp 추가 함수 - A _ a 순서에 맞게 배열하는 함수 -> 실행부에 넘김
// 	// envp 제거 함수???? -> 실행부에 넘김
// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		token_list = (t_list *)ft_tokenizer(input);
// 		if (token_list != 0)
// 		{
// 			if (ft_syntax_analysis(token_list) == FT_SUCCESS)
// 			{
// 				// 성공한 경우에만 환경 변수 확장
// 				if (ft_token_expansion(token_list, dll_envp_tower) == FT_SUCCESS)
// 				{
// 					token_tree = ft_syntax_parse_tree(token_list);
// 					if (token_tree != 0)
// 					{
// 						//작업 임시 테스트
// 						test_print_token_lst(token_list);
// 						ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);


// 						ft_tree_node_pre_traversal(token_tree, &test_tree_node_check_for_content);
// 						ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
// 					}
// 				}
// 			}

// 		}
// 		system("leaks minishell | grep LEAK");
// 	}
// 	return (FT_SUCCESS);
// }


// 원하는 동작 기존에 ((t_tree_cmd *)node->content)->argv에 있는 값을 이용해서

// ((t_exe_cmd *)node->content)->???? 로 쓸수 있게끔 바꾸고 싶다.


// 이걸 바꾸던가 아니면 파싱부를 수정해서 t_tree_cmd에 file_path를 추가해야 되겠다.



// void exe_cmd_set(t_tree_node *node)
// {
// 	// 그 전에 있던 걸 프리를 해줘야 될것 같기도 하다.


// 	node->content = (t_exe_cmd *)malloc(sizeof(t_exe_cmd));
// 	if(node->content == 0)
// 		return (FT_ERROR);
// 	((t_exe_cmd *)(node->content))->cmd_name = ft_strdup()


// }

// ex) command == ls 처처럼  file_path를 알아야할 command ls,cat,echo이런애들


