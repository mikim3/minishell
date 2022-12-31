/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:57:52 by kshim             #+#    #+#             */
/*   Updated: 2022/12/31 17:57:27 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_tokenizer.h"
#include "../../include/ft_doubly_linked_list.h"
#include "../../include/ft_token_expansion.h"


#include <stdio.h>

int	ft_token_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	t_d_list	*envp_head;

	token_node = token_list;
	envp_head = dll_envp_tower->head;
	while (ft_token_what_type(token_node) != TKN_NULL)
	{
		if (ft_token_is_expandable(token_node) == BOOL_TRUE)
		{
			if (ft_token_str_expansion(&(((t_tkn *)token_node->content)->str), envp_head, EXPAND_ALL) == FT_ERROR)
				return (FT_ERROR);
		}
		token_node = token_node->next;
	}
	return (FT_SUCCESS);
}

int	ft_token_str_expansion(char **token_str, t_d_list *mnsh_envp, int expand_mode)
{
	char	*pos;
	char	*ret_str;
	char	*start;
	int		len;

	pos = *token_str;
	ret_str = 0;
	start = pos;
	len = 0;
	while (*pos != '\0')
	{
		// 지금까지 읽은 값 추가하는 메커니즘 필요함 + 추가하는 알고리즘도 검토
		if (len != 0 && (*pos == '$' || *pos == '\"' || *pos == '\''))
		{
			if (ft_token_expand_str_control_without_expand(
				&ret_str, start, len) == FT_ERROR)
				return (FT_ERROR);
			else
			{
				start = pos;
				len = 0;
			}
		}
		if ((expand_mode == EXPAND_ALL || expand_mode == EXPAND_ENV_ONLY) && *pos == '$')
		{
			if (ft_token_expand_expansion_sign(&pos, &ret_str, mnsh_envp) == FT_ERROR)
				return (free(ret_str), FT_ERROR);
			start = pos;
		}
		else if ((expand_mode == EXPAND_ALL || expand_mode == EXPAND_QUOTE_ONLY) && *pos == '\"')
		{
			if (ft_token_expand_double_quotes(&pos, &ret_str, mnsh_envp, expand_mode) == FT_ERROR)
				return (free(ret_str), FT_ERROR);
			pos++;
			start = pos;
		}
		else if ((expand_mode == EXPAND_ALL || expand_mode == EXPAND_QUOTE_ONLY) && *pos == '\'')
		{
			if (ft_token_expand_single_quotes(&pos, &ret_str) == FT_ERROR)
				return (free(ret_str), FT_ERROR);
			pos++;
			start = pos;
		}
		else
		{
			pos++;
			len++;
		}
	}
	if (ret_str == 0)
		return (FT_SUCCESS);
	free(*token_str);
	*token_str = ret_str;
	return (FT_SUCCESS);
}

		// mode '\0'인데 $ 또는 quote 출현 시
			// 이전까지의 문자 잘라내고 시작점, 길이 설정
			// 기존 문자열에 새로 만든 문자열 붙이기
			// $ 또는 quote에 해당하는 모드 문자 설정
		// mode '\0'인데 특수문자 안나온 경우
			// 아마 else 동작
		// mode '$' 인데 ' ' 또는 '$' 또는 quote 출현 시
			// 이전까지의 문자 잘라내고 시작점, 길이 설정
			// 잘린 문자를 mnsh_envp에서 탐색
				// 존재할 경우 value 값을 strdup
				// 없을 경우 빈 문자열 strdup
			// 기존 문자열에 새로 확장한 문자열 붙이기
			// $ 또는 quote에 해당하는 모드 문자 설정


	// double_quote 안에서 이 함수 호출할 수도 있음 - 공백 처리 필요
int	ft_token_expand_expansion_sign(char **pos, char **ret_str, t_d_list *mnsh_envp)
{
	int		len;
	char	*start;
	char	*tmp_buffer;
	char	*tmp_str;

	len = 0;
	start = ++(*pos);
	tmp_buffer = 0;
	tmp_str = 0;
	while (**pos != '\0' && **pos != '$' && **pos != '\''
		&& **pos != '\"' && ft_isspace(**pos) == BOOL_FALSE)
	{
		len++;
		(*pos)++;
	}
	if (ft_token_expand_str_control_with_expand(
			ret_str, start, len, mnsh_envp) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

// 이 함수 안에서 ft_token_expand_expansion_sign 함수를 실행하는 경우가 있을 수 있다.
// 이 때, len 처리를 어떻게 하는게 좋을까?
	// 만약 ft_token_expand_expansion_sign 함수 내부 len을 가져오는게 불가능하다면,
	// len을 사용하지 않는 구조로 만드는게 더 바람직하지 않을까?
		// 아니다. 저 함수 호출하면 len 초기화하고 뒤 문자를 다시 붙이게 만들어도 괜찮을 것 같다.

		// 달러 나오면 지금까지 읽은 것 이어 붙이기
		// len 초기화
		// 시작 위치 재설정 준비
int	ft_token_expand_double_quotes(char **pos, char **ret_str, t_d_list *mnsh_envp, int expand_mode)
{
	int		len;
	char	*start;
	char	*tmp_buffer;
	char	*tmp_str;

	len = 0;
	start = ++(*pos);
	tmp_buffer = 0;
	tmp_str = 0;
	while (**pos != '\"')
	{
		if ((expand_mode == EXPAND_ALL) && **pos == '$')
		{
			if (ft_token_expand_str_control_without_expand(
				ret_str, start, len) == FT_ERROR)
				return (FT_ERROR);
			if (ft_token_expand_expansion_sign(pos, ret_str, mnsh_envp) == FT_ERROR)
				return (FT_ERROR);
			len = 0;
			start = *pos;
		}
		else
		{
			len++;
			(*pos)++;
		}
	}
	if (ft_token_expand_str_control_without_expand(
		ret_str, start, len) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_token_expand_single_quotes(char **pos, char **ret_str)
{
	int		len;
	char	*start;
	char	*tmp_buffer;
	char	*tmp_str;

	len = 0;
	start = ++(*pos);
	tmp_buffer = 0;
	tmp_str = 0;
	while (**pos != '\'')
	{
		len++;
		(*pos)++;
	}
	if (ft_token_expand_str_control_without_expand(
		ret_str, start, len) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

// 잘라 붙이기 함수 독립시킬 수 있지 않을까?
	// tmp_str에 strndup(start, len)를 한다.
	// tmp_str을 mnsh_envp의 key들과 strcmp한다.
		// strcmp == 0이 있을 경우 strdup로 value를 카피한다. - 절차 조정
		// strcmp == 0이 없을 경우, strdup로 빈 문자열을 만든다. - 절차 조정
	// tmp_str에 ret_str을 담는다.
	// ret_str에 strjoin(tmp_str, tmp_buffer)을 한다.
	// tmp_str를 해제한다.
	// tmp_buffer를 해제한다.
int	ft_token_expand_str_control_with_expand(
	char **ret_str, char *start, int len, t_d_list *mnsh_envp)
{
	char	*tmp_buffer;
	char	*tmp_str;

	tmp_buffer = 0;
	tmp_str = 0;
	tmp_str = ft_strndup(start, len);
	if (tmp_str == 0)
		return (FT_ERROR);
	tmp_buffer = ft_compare_str_to_mnsh_envp_keys(tmp_str, mnsh_envp);
	free(tmp_str);
	if (tmp_buffer == 0)
	{
		tmp_buffer = ft_strdup("");
		if (tmp_buffer == 0)
			return (FT_ERROR);
	}
	tmp_str = *ret_str;
	if (tmp_str == 0)
		*ret_str = ft_strjoin("", tmp_buffer);
	else
		*ret_str = ft_strjoin(tmp_str, tmp_buffer);	
	free(tmp_buffer);
	if (*ret_str == 0)
	{
		*ret_str = tmp_str;
		return (FT_ERROR);
	}
	if (tmp_str != 0)
		free(tmp_str);
	return (FT_SUCCESS);
}

int	ft_token_expand_str_control_without_expand(char **ret_str, char *start, int len)
{
	char	*tmp_buffer;
	char	*tmp_str;

	tmp_buffer = 0;
	tmp_str = 0;
	tmp_buffer = ft_strndup(start, len);
	if (tmp_buffer == 0)
		return (FT_ERROR);
	tmp_str = *ret_str;
	if (tmp_str == 0)
		*ret_str = ft_strjoin("", tmp_buffer);
	else
		*ret_str = ft_strjoin(tmp_str, tmp_buffer);	
	free(tmp_buffer);
	if (*ret_str == 0)
	{
		*ret_str = tmp_str;
		return (FT_ERROR);
	}
	free(tmp_str);
	return (FT_SUCCESS);
}

char	*ft_compare_str_to_mnsh_envp_keys(char *str, t_d_list *mnsh_envp)
{
	char	*cp_value;
	
	cp_value = 0;
	while (mnsh_envp != 0)
	{
		if (ft_strcmp(str, ((t_envp_content *)mnsh_envp->content)->key) == FT_SUCCESS)
		{
			cp_value = ft_strdup(((t_envp_content *)mnsh_envp->content)->value);
			if (cp_value == 0)
				return (0);
			return (cp_value);
		}
		mnsh_envp = mnsh_envp->next;
	}
	return (0);
}

int	ft_token_is_expandable(t_list *token)
{
	// 각 type에 대한 동작
	return (((t_tkn *)token->content)->expandable);
}

int	ft_token_check_for_quote(t_list *token)
{
	char	*str_pos;

	str_pos = ft_token_what_str(token);
	while (*str_pos != '\0')
	{
		if (*str_pos == '\'' || *str_pos == '\"')
		{
			return (BOOL_TRUE);
		}
	}
	return (BOOL_FALSE);
}
