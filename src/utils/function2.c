/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:30:01 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 12:25:05 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/ft_wrapper_functions.h"

#include "../../include/ft_minishell.h"

int	ft_open(const char *str, int flags, mode_t mode)
{
	int	ret_val;

	ret_val = open(
				str, flags, mode);
	if (ret_val == -1)
		exitcode_with_err("open()", strerror(errno), 1);
	return (ret_val);
}

int	ft_close(int fd)
{
	int	ret_val;

	ret_val = close(fd);
	if (ret_val == -1)
		exitcode_with_err("close()", strerror(errno), 1);
	return (ret_val);
}

pid_t ft_fork(void)
{
	pid_t	ret_val;

	ret_val = fork();
	if (ret_val == -1)
		exitcode_with_err("fork()", strerror(errno), 1);
	return (ret_val);
}

pid_t ft_pipe(int fd[2])
{
	pid_t	ret_val;

	ret_val = pipe(fd);
	if (ret_val == -1)
		exitcode_with_err("pipe()", strerror(errno), 1);
	return (ret_val);
}

int	ft_dup2(int oldfd, int newfd)
{
	int	ret_val;

	ret_val = dup2(oldfd, newfd);
	if (ret_val == -1)
		exitcode_with_err("dup2()", strerror(errno), 1);
	return (ret_val);
}

int	ft_access(const char *file, int flags)
{
	int	ret_val;

	ret_val = access(
				file, flags);
	if (ret_val == -1)
		exitcode_with_err("access()", strerror(errno), 1);
	return (ret_val);
}

int ft_fstat(int fd, struct stat *buf)
{
	int	ret_val;

	ret_val = fstat(
				fd, buf);
	if (ret_val == -1)
		exitcode_with_err("fstat()", strerror(errno), 1);
	return (ret_val);
}
