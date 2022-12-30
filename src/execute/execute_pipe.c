/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:01:23 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 15:15:50 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"
#include <fcntl.h>

// 공통 전제
	// pipe를 여는 조건 및 처리하는 데이터는?
		// pipe가 열렸다면, 다음 파이프가 존재한다는 걸 자식 프로세스에게 알려야한다.
			// next_pipe_check = BOOL_TRUE;

	// 새로운 pipe의 각 end는 언제 닫는게 맞을까? !!!!! 다음 pipe 존재 여부따라 동작 달라짐. 수정 필요!!!
		// 1. 부모	- '''fork 후'''에 pipe[P_WRITE] 닫기
		//		   - pre_pipe_check = BOOL_TRUE;
		//		   - pre_pipe_read_end = pipe[P_READ];
		//		   - 다음 fork 준비
			// 다음 (오른쪽) pipeline 있는지 보고 next_pipe_check = BOOL_TRUE 혹은 BOOL_FALSE하는 기능 필요
		// 2. 자식	- pipe[P_READ] 닫기
		//		   - pre_pipe_check == BOOL_TRUE라면
		//				pre_pipe_read_end랑 stdin의 dup2
		//				inpue_fd = pre_pipe_read_end
		//		   - next_pipe_check == BOOL_TRUE라면
		//				pipe[P_WRITE]랑 stdout의 dup2
		//		   		output_fd = pipe[P_WRITE]
			//		**위 두 조건이 FALSE인 경우에는
			//		redir type 노드가 존재할 경우에 그쪽으로 redirect될 것

// -------------- 여기까진 초기 구현 설정한 것으로 보임 - 정리는 덜 됨


// redir에서 호출하는 함수
	// 필요한 자료
		// 1. input fd, output fd (여러번 redirect 될 수 있음. 항상 저장 필요 -> 구조체에 담기)
		// 2. pipe의 read, right end? => 이건 pipeline 단계에서 처리할 것으로 보임
		//
	// 동작
		

//
//// filename에 경로 붙이기 getcwd

int	execute_redir(t_tree_node *node, t_pipe *m_pipe)
{
	int		redir_fd;
	char	*redir;
	char	*file_name;
	int		ret_val;

	redir_fd = -1;
	redir = ((t_tree_redir *)node->content)->redir;
	file_name = ((t_tree_redir *)node->content)->file_name;
	if (ft_isdigit(*redir) == BOOL_TRUE)
	{
		redir_fd = ft_atoi(redir);
		if (redir_fd < 0)
		{
			return (FT_ERROR);
		}
		while (ft_isdigit(*redir) == BOOL_FALSE)
			redir++;
	}
	if (ft_strcmp(redir, "<") == FT_SUCCESS)
	{
		ret_val = ft_redir_infile(file_name, m_pipe, redir_fd);
		printf("redir - infile\n");
	}
	else if (ft_strcmp(redir, ">") == FT_SUCCESS)
	{
		ret_val = ft_redir_outfile(file_name, m_pipe, redir_fd);
		printf("redir - outfile\n");
	}
	else if (ft_strcmp(redir, ">>") == FT_SUCCESS)
	{
		ret_val = ft_redir_append(file_name, m_pipe, redir_fd);
		printf("redir - append\n");
	}
	else if (ft_strcmp(redir, "<<") == FT_SUCCESS)
	{
		printf("redir - heredoc\n");
	}
	if (ret_val == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_redir_infile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	// file_name = ft_상대경로_해석_함수();
	// if (file_name == 0)
	// 	return (FT_ERROR);
	if (access(file_name, F_OK | R_OK) == 0)
	{
		// pipex와 동작 다르니 주의 (파일 redir 전에 redir이미 했을 수가 있음)
		file_fd= open(file_name, O_RDWR);
	}
	else
		return (FT_ERROR);
	if (file_fd== -1)
		return (FT_ERROR);
	if (redir_fd == -1)
	{
		dup2(file_fd, m_pipe->infile_fd);
		close(file_fd);
	}
	else
	{
		dup2(file_fd, redir_fd);
		close(file_fd);
	}
	return (FT_SUCCESS);
}

int	ft_redir_outfile(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	// file_name = ft_상대경로_해석_함수();
	// if (file_name == 0)
	// 	return (FT_ERROR);
	file_fd= open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (file_fd== -1)
		return (FT_ERROR);
	if (redir_fd == -1)
	{
		dup2(file_fd, m_pipe->outfile_fd);
		close(file_fd);
	}
	else
	{
		dup2(file_fd, redir_fd);
		close(file_fd);
	}
	return (FT_SUCCESS);
}

int	ft_redir_append(char *file_name, t_pipe *m_pipe, int redir_fd)
{
	int	file_fd;
	// file_name = ft_상대경로_해석_함수();
	// if (file_name == 0)
	// 	return (FT_ERROR);
	file_fd= open(file_name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (file_fd== -1)
		return (FT_ERROR);
	if (redir_fd == -1)
	{
		dup2(file_fd, m_pipe->outfile_fd);
		close(file_fd);
	}
	else
	{
		dup2(file_fd, redir_fd);
		close(file_fd);
	}
	return (FT_SUCCESS);
}

// int	ft_redir_here_doc()
// {

// }


// 상대 경로 가져오는 함수
