/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:47 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 13:14:28 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	check_env_key(char *key)
{
	if (ft_strcmp(key, "$?") == 0)
		return (1);
	if (allowed_character(key))
		return (0);
	return (1);
}

int	allowed_character(char *str)
{
	int	index;

	index = 0;
    //key값으로 첫글자 숫자는 불허
	if ('0' <= str[0] && str[0] <= '9')
		return (0);
	while (str[index])
	{
		if (!(('a' <= str[index] && str[index] <= 'z')
				|| ('A' <= str[index] && str[index] <= 'Z')
				|| ('0' <= str[index] && str[index] <= '9')
				|| '_' == str[index]))
		{
		    return (0);
		}
        index++;
	}
	return (1);
}
