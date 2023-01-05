/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:57:52 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 16:58:09 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_expansion(t_list *token_list, t_detower *dll_envp_tower)
{
	t_list		*token_node;
	t_d_list	*envp_head;

	token_node = token_list;
	envp_head = dll_envp_tower->head;
	while (ft_token_type(token_node) != TKN_NULL)
	{
		if (ft_token_is_expandable(token_node) == BOOL_TRUE)
		{
			if (ft_token_str_expansion(\
				&(((t_tkn *)token_node->content)->str), envp_head, \
					EXPAND_ALL) == FT_ERROR)
			{
				ft_free_tokenizer_list_and_token(\
					&token_list, 0, TKN_TKNIZE_SUCCESSED);
				exit(137);
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
	if (**pos == '?')
	{
		len++;
		(*pos)++;
		if (ft_token_expand_str_control_with_expand(
				ret_str, start, len, mnsh_envp) == FT_ERROR)
			return (FT_ERROR);
		return (FT_SUCCESS);
	}
	while ((('a' <= **pos && **pos <= 'z')
			|| ('A' <= **pos && **pos <= 'Z')
			|| ('0' <= **pos && **pos <= '9')
			|| '_' == **pos))
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
			if (ft_token_expand_expansion_sign(
					pos, ret_str, mnsh_envp) == FT_ERROR)
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
