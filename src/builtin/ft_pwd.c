/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:14:33 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 14:59:07 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_pwd(t_pipe *pipe_value)
{
	char	*output;

	g_exit_code = 0;
	output = getcwd(NULL, 0);
	output = ft_strjoin_infree(output, ft_strdup("\n"));
	write(pipe_value->outfile_fd, output, ft_strlen(output));
	free(output);
}
