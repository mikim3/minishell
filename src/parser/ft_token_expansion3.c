/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:48:15 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 16:13:49 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_token_expand_str_control_with_expand(
	char **ret_str, char *start, int len, t_d_list *mnsh_envp)
{
	char	*tmp_buffer;
	char	*tmp_str;

	tmp_str = ft_strndup(start, len);
	if (tmp_str == 0)
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	if (*tmp_str == '?')
		tmp_buffer = ft_itoa(g_exit_code);
	else
		tmp_buffer = ft_compare_str_to_mnsh_envp_keys(tmp_str, mnsh_envp);
	free(tmp_str);
	if (tmp_buffer == 0)
	{
		tmp_buffer = ft_strdup("");
		if (tmp_buffer == 0)
			return (exitcode_with_err("malloc", \
				strerror(errno), 140), FT_ERROR);
	}
	if (ft_token_expand_str_control_attach(
			ret_str, &tmp_str, &tmp_buffer) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_token_expand_str_control_without_expand(
		char **ret_str, char *start, int len)
{
	char	*tmp_buffer;
	char	*tmp_str;

	tmp_buffer = ft_strndup(start, len);
	if (tmp_buffer == 0)
		return (FT_ERROR);
	if (ft_token_expand_str_control_attach(
			ret_str, &tmp_str, &tmp_buffer) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_token_expand_str_control_attach(
		char **ret_str, char **tmp_str, char **tmp_buffer)
{
	*tmp_str = *ret_str;
	if (*tmp_str == 0)
		*ret_str = ft_strjoin("", *tmp_buffer);
	else
		*ret_str = ft_strjoin(*tmp_str, *tmp_buffer);
	free(*tmp_buffer);
	if (*ret_str == 0)
	{
		*ret_str = *tmp_str;
		return (exitcode_with_err("malloc", strerror(errno), 140), FT_ERROR);
	}
	if (*tmp_str != 0)
		free(*tmp_str);
	return (FT_SUCCESS);
}

char	*ft_compare_str_to_mnsh_envp_keys(char *str, t_d_list *mnsh_envp)
{
	char	*cp_value;

	cp_value = 0;
	while (mnsh_envp != 0)
	{
		if (ft_strcmp(str,
				((t_env_ctnt *)mnsh_envp->content)->key) == FT_SUCCESS)
		{
			cp_value = ft_strdup(((t_env_ctnt *)mnsh_envp->content)->value);
			if (cp_value == 0)
				return (0);
			return (cp_value);
		}
		mnsh_envp = mnsh_envp->next;
	}
	return (0);
}
