/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:30:01 by kshim             #+#    #+#             */
/*   Updated: 2023/01/04 16:27:17 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

#include <fcntl.h>

int	ft_open(const char *str, int flags, mode_t mode)
{
	int	ret_val;

	ret_val = open(
				"/tmp/.mnsh_here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
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
