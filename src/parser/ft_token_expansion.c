/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:57:52 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 18:16:16 by kshim            ###   ########.fr       */
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

int	ft_token_str_expansion(
		char **token_str, t_d_list *mnsh_envp, int expand_mode)
{
	t_expand	*expand;

	if (ft_token_expand_init_struct(&expand, token_str) == FT_ERROR)
		return (FT_ERROR);
	while (*(expand->pos) != '\0')
	{
		if (expand->len != 0 && (*(expand->pos) == '$' \
			|| *(expand->pos) == '\"' || *(expand->pos) == '\''))
		{
			if (ft_token_expand_str_control_without_expand(
					&(expand->ret_str), expand->start, expand->len) == FT_ERROR)
				return (ft_token_expand_free_struct(&expand), FT_ERROR);
			else
			{
				expand->start = expand->pos;
				expand->len = 0;
			}
		}
		if ((expand_mode == EXPAND_ALL || expand_mode == EXPAND_ENV_ONLY) \
			&& *(expand->pos) == '$')
		{
			if (ft_token_expand_expansion_sign(expand, mnsh_envp) == FT_ERROR)
				return (ft_token_expand_free_struct(&expand), FT_ERROR);
			expand->start = expand->pos;
			expand->len = 0;
		}
		else if ((expand_mode == EXPAND_ALL \
			|| expand_mode == EXPAND_QUOTE_ONLY) && *(expand->pos) == '\"')
		{
			if (ft_token_expand_double_quotes(expand, mnsh_envp, expand_mode) == FT_ERROR)
				return (ft_token_expand_free_struct(&expand), FT_ERROR);
			expand->pos++;
			expand->start = expand->pos;
			expand->len = 0;
		}
		else if ((expand_mode == EXPAND_ALL \
			|| expand_mode == EXPAND_QUOTE_ONLY) && *(expand->pos) == '\'')
		{
			if (ft_token_expand_single_quotes(expand) == FT_ERROR)
				return (ft_token_expand_free_struct(&expand), FT_ERROR);
			expand->pos++;
			expand->start = expand->pos;
			expand->len = 0;
		}
		else
		{
			expand->pos++;
			expand->len++;
		}
	}
	if (expand->len != 0)
	{
		if (ft_token_expand_str_control_without_expand(
				&(expand->ret_str), expand->start, expand->len) == FT_ERROR)
			return (ft_token_expand_free_struct(&expand), FT_ERROR);
	}
	if (expand->ret_str == 0)
		return (FT_SUCCESS);
	free(*token_str);
	*token_str = ft_strdup(expand->ret_str);
	if (*token_str == 0)
		return (FT_ERROR);
	ft_token_expand_free_struct(&expand);
	return (FT_SUCCESS);
}

int	ft_token_expand_init_struct(t_expand **expand, char **token_str)
{
	*expand = (t_expand *)malloc(sizeof(t_expand));
	if (*expand == 0)
		return (FT_ERROR);
	(*expand)->pos = *token_str;
	(*expand)->ret_str = 0;
	(*expand)->start = *token_str;
	(*expand)->len = 0;
	return (FT_SUCCESS);
}

void	ft_token_expand_free_struct(t_expand **expand)
{
	(*expand)->pos = 0;
	(*expand)->len = 0;
	(*expand)->start = 0;
	if ((*expand)->ret_str != 0)
		free((*expand)->ret_str);
	(*expand)->ret_str = 0;
	free(*expand);
	*expand = 0;
}
