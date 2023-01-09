/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_function3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/09 09:30:47 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_char_free(char *str)
{
	if (str)
	{
		free(str);
	}
	else
		return ;
}

char	*ft_getenv(char *path_name)
{
	char	*output;

	output = getenv(path_name);
	if (output == NULL)
		exitcode_with_err("getenv()", strerror(errno), 1);
	return (output);
}
