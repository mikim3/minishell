/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 14:13:45 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_free_string_ptr_arr(char **argv)
{
	int	i;

	i = 0;
	if (argv == 0)
		return ;
	while (argv[i] != 0)
	{
		free(argv[i]);
		argv[i] = 0;
		i++;
	}
	free(argv);
	return ;
}
