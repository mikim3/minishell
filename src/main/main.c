/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/27 15:29:59 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	main_init(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);  //  시그널 ^C 출력안되게 설장하기
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// set_signal(SHE, SHE); // 시그널
	g_exit_code = 0;
}

void	init_pipe(t_pipe *m_pipe)
{
	m_pipe->next_pipe_check = 0;
	m_pipe->pre_pipe_check = 0;
	m_pipe->pipe_read_end = STDIN_FILENO;
	m_pipe->pipe_write_end = STDOUT_FILENO;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
}


int	main(int argc, char **argv, char **envp)
{
	t_list		*token_list;
	char		*input;
	t_tree_node	*token_tree;
	t_detower	*dll_envp_tower;
	char		**mnsh_envp;
	t_pipe		m_pipe;
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
		if (input == NULL) //  Ctrl + D를 누르면 input은 NULL이 들어옴
		{
			printf("see you later \n");
			exit(0);
		}
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
					init_pipe(&m_pipe);
					
					ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
					// ft_execute_tree(token_tree,dll_envp_tower, &m_pipe);
					// ft_tree_node_pre_traversal(token_tree, &test_tree_node_check_for_content);
					
					// simple_cmd set용함수   입력받은 값이 있어야함  token_tree로 탐색하면서 NODE_SIMPLE_CMD
					ft_tree_node_pre_traversal_exe_cmd_set(token_tree, input, &exe_cmd_set);

					// 실행용
					ft_tree_node_pre_traversal2(token_tree, dll_envp_tower, &m_pipe, &ft_execute_tree);
					// ft_tree_node_pre_traversal(token_tree, &ft_execute_tree_node);
					ft_tree_node_post_traversal(token_tree, &ft_free_a_tree_node);
				}
			}
		}
		// tcsetattr(STDIN_FILENO, TCSANOW, &term);
		// system("leaks minishell | grep LEAK");
	}
	return (FT_SUCCESS);
}

// ((t_tree_cmd *)token_tree->content)->argv
void exe_cmd_set(t_tree_node *node)
{

	// if (token_tree->type == NODE_SIMPLE_CMD)
	// {
	printf("in simple_cmd_set token_tree->type == NODE_SIMPLE_CMD \n");
	printf("%s \n",input);
	// malloc 같은거 다시 생각해보기

	simple_cmd->argv = 

	// 파일 위치 set
	// simple_cmd->file_path = set_file_path();

	token_tree->content = 
	
	// cmd에 있는걸 simple_cmd에 어떻게 넣지??
		// 

	// }

}

// ex) command == ls 처처럼  file_path를 알아야할 command ls,cat,echo이런애들
char *exe_cmd_file_path_set(t_env env,char *command)
{
	char	*file_path;

	// if (ft_strncmp(command, "/", 1) == 0) // /
	// {
	// 	file_path = ft_strdup(command);
	// }
	// else if ()

	else //그냥 echo haha 처럼 그냥 입력
	{

	}
	return (file_path);
}


