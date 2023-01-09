/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:44:44 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 14:13:55 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	exitcode_with_err(char *str, char *str_error, int exit_code)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (str_error)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str_error, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_code = exit_code;
}

void	exitcode_with_err2(char *str, \
	char *str_err1, char *str_err2, int exit_code)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str_err1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str_err2, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_code = exit_code;
}
