/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:25:19 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/29 17:25:40 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	double_char_free(char **double_char)
{
	int	i;

	i = 0;
	while (double_char[i])
	{
		free(double_char[i]);
		i++;
	}
	free(double_char);
}
