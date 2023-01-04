/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 13:31:46 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

static int	ft_strcmp_option_check(char *s1)
{
	size_t				i;

	i = 0;
	if (s1[i] != '-')
		return (0); // option이 아니다.
	if (s1[1]) // '-'다음 글자가 존재함
		i++;
	else	 // '-' 다음 비어있으면 option이 아니다.  
		return (0);
	while (i < ft_strlen(s1))
	{
		if (s1[i] != 'n')//ㅎㅏ나라도 n이 아니면 0반환 옵션이 아니다.
			return (0);
		i++;
	}
	return (1); //결국 끝까지 n만 있다면 이건 option이 맞다.
}

// no_option_index --> 어디부터 옵션이 아닌 str이 나오는지 판단 여기부터는  
static int     use_u_option_check(t_tree_cmd *cmd, int *no_option_index)
{
    int index;
    int use_u_option_check;  //-n 옵션 인정처리

    index = 0;
    use_u_option_check = 0;  // 기본적으로 옵션 안 쓴상태

    while(cmd->cmd_argv[++index])
	{
		if ((ft_strcmp_option_check(cmd->cmd_argv[index]) == 1))  // n이 맞는지 판단
			use_u_option_check = 1; 
		else
			break;
	}
	*no_option_index = index; // 옵션을 넘긴 시작지점을 넘겨준다.
    return (use_u_option_check);
}

void	ft_echo(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	char	*output;
	int		index;
	int		use_u_option;   // -n 옵션 사용 여부   1: -n씀  
    int     argv_start_str; //argv의 몇번째 위치부터가 option이 아닌가를 체크 ex) echo -n -n -n haha   이면 haha부터 글자를 출력해야 되겠지

	index = 0;
	argv_start_str = 0;
	use_u_option = use_u_option_check(cmd, &(argv_start_str));  //return 두개가 필요할경우 이렇게 넣는게 아니라 인자로 주소값 줘서 함수안에서 삽입할 필요가 있을수도 // index옵션이 argv[]를 차지하는 만큼 넘긴다.
	output = NULL;
    index = argv_start_str; // echo -n -n hellow word 다음과 같은 경우 index 가 3부터(출력을 3부터 값 넣는거는 처음에 ++이니까 2)시작해야함
	while (cmd->cmd_argv[index])
	{
		output = ft_strjoin_infree(output, ft_strdup(cmd->cmd_argv[index]));
		if (cmd->cmd_argv[index + 1])
			output = ft_strjoin_infree(output, ft_strdup(" ")); 
		index++;
	}
	if (output != NULL)
		write(pipe_value->outfile_fd, output, ft_strlen(output));
	if (!use_u_option)
		write(pipe_value->outfile_fd, "\n", 1);
	free(output);
}
