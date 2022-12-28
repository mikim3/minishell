/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:32:02 by kshim             #+#    #+#             */
/*   Updated: 2022/07/23 09:54:15 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start_index;
	size_t	end_index;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	start_index = 0;
	end_index = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start_index]) && s1[start_index] != '\0')
		start_index++;
	while (ft_strrchr(set, s1[end_index]))
	{
		if (end_index == 0)
			break ;
		end_index--;
	}
	if (start_index > end_index)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end_index - start_index + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (s1 + start_index), (end_index - start_index + 2));
	return (str);
}
