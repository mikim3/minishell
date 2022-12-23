/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:19:28 by kshim             #+#    #+#             */
/*   Updated: 2022/10/30 17:50:14 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_sep(char const *s, char c);
static char		**ft_distribute_str(char **strs, char const *s, char c);
static size_t	ft_sep_length(char const *str_pos, char c);
static void		ft_strs_clear(char **strs, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	len;

	len = ft_count_sep(s, c);
	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (strs == 0)
		return (0);
	strs[len] = 0;
	return (ft_distribute_str(strs, s, c));
}

static size_t	ft_count_sep(char const *s, char c)
{
	size_t	i;
	size_t	ret;

	ret = 0;
	i = 0;
	if (s[0] != c && s[0] != '\0')
		ret++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (ret == 0 && s[i + 1] == '\0')
				return (0);
			if (s[i + 1] != c && s[i + 1] != '\0')
				ret++;
		}
		i++;
	}
	return (ret);
}

static char	**ft_distribute_str(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	idx;

	i = 0;
	idx = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = ft_sep_length((s + i), c);
			strs[idx] = (char *)malloc(sizeof(char) * (j + 1));
			if (strs[idx] == 0)
			{
				ft_strs_clear(strs, s, c);
				return (0);
			}
			ft_strlcpy(strs[idx++], (s + i), (j + 1));
			i = i + j;
		}
		else
			i++;
	}
	return (strs);
}

static size_t	ft_sep_length(char const *str_pos, char c)
{
	size_t	i;

	i = 0;
	while (*(str_pos + i) != c && *(str_pos + i) != '\0')
		i++;
	return (i);
}

static void	ft_strs_clear(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_count_sep(s, c);
	while (i < len)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = 0;
}
