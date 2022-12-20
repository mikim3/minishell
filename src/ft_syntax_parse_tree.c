/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_parse_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:46:11 by kshim             #+#    #+#             */
/*   Updated: 2022/12/20 15:50:07 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_tree.h"
#include "../include/ft_tokenizer.h"

t_tree_node	*ft_syntax_parse_tree(t_list *token_list, int is_root)
{
	
	// 앞에서 부터 읽는다.env
	
		// redir 나올 경우 -> 다음 토큰 word와 함께 redirection 구성한다
		// word 나올 경우 -> cmd_argv에 추가할 준비를 한다. (list 사용해서 저장했다가 한 번에 할당)
		// pipe 나올 경우 -> 다음 pipeline으로 분화한다.
	
	// 노드 종류가 결정되었다면, 추가를 시도한다
		// redir의 경우, redir 종류에 따라 in, out에 add_node_bfs로 저장한다.
		// word의 경우, cmd_argv_list에 추가한다.
		// pipe의 경우, cmd_argv_list를 cmd_argv로 만들어 저장한 후에 
			// 'pipeline'의 오른쪽을 대상으로 syntax_parse_tree를 재귀 호출하고 함수 종료 준비를 한다.
				// 만약 '오류값'을 반환 받았다면 '오류값'을 반환한다.
		// NULL 토큰을 만난 경우 함수를 종료한다.
			// 할당 오류 등의 문제가 발생했다면 '오류값' 반환한다.
	//**** 재귀적으로 처리할 떄, root stack임을 알아야 할당 해제가 수월할 것 같다.
	// 어떻게 root stack임을 알 수 있을까? (호출할 때 인자 줄까?)
	if (is_root == BOOL_TRUE)
	{
		// 해제 작업
	}
	token_list = 0;
	return (0);
}
