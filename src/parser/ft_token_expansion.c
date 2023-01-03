/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:57:52 by kshim             #+#    #+#             */
/*   Updated: 2023/01/03 12:35:28 by kshim            ###   ########.fr       */
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
			{
				ft_free_tokenizer_list_and_token(&token_list, 0, TKN_TKNIZE_SUCCESSED);
				return (FT_ERROR);
			}	
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
		if (len != 0 && (*pos == '$' || *pos == '\"' || *pos == '\''))
		{
			if (ft_token_expand_str_control_without_expand(
				&ret_str, start, len) == FT_ERROR)
				return (free(ret_str), FT_ERROR);
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
	if (len != 0)
	{
		if (ft_token_expand_str_control_without_expand(
			&ret_str, start, len) == FT_ERROR)
			return (free(ret_str), FT_ERROR);
	}
	if (ret_str == 0)
		return (FT_SUCCESS);
	free(*token_str);
	*token_str = ret_str;
	return (FT_SUCCESS);
}

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
	// if (!(('a' <= str[index] && str[index] <= 'z')
	// 		|| ('A' <= str[index] && str[index] <= 'Z')
	// 		|| ('0' <= str[index] && str[index] <= '9')
	// 		|| '_' == str[index]))
	while (**pos != '\0' && **pos != '$' && **pos != '\'' && **pos != '\n'
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

int	ft_token_expand_str_control_with_expand(
	char **ret_str, char *start, int len, t_d_list *mnsh_envp)
{
	char	*tmp_buffer;
	char	*tmp_str;

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
	if (tmp_str != 0)
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
		str_pos++;
	}
	return (BOOL_FALSE);
}
