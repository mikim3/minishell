/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 17:36:52 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_execve(char *file, char **argv, char **envp)
{
	if (execve(file, argv, envp) == -1)
	{
		printf("errno %d \n",errno);
		if (errno == ENOENT) //  No such file or directory
			exitcode_with_err(argv[0], strerror(errno), 127);
		else if (errno == EACCES) //  Permission denied
			exitcode_with_err(argv[0], strerror(errno), 126);
		else
			exitcode_with_err(argv[0], strerror(errno), 1);
	}
	return ;
}

int	ft_chdir(char *dir)
{
	int		return_value;

	return_value = chdir(dir);
	if (return_value == -1)
	{
		printf("errno %d \n",errno);
		if (errno == ENOENT) //  No such file or directory
			exitcode_with_err("cd", strerror(errno), 127);  // 첫 인자 chdir()이 맞을까?
		else if (errno == EACCES) //  Permission denied
			exitcode_with_err("cd", strerror(errno), 126);
		else
			exitcode_with_err("cd", strerror(errno), 1);
	}
	return (return_value);
}

char	*ft_getcwd(char *buf, size_t size)
{
	char *output;

	output = getcwd(NULL, 0);
	if (output == NULL)
	{
		exitcode_with_err("pwd", strerror(errno), 1);  // 첫 인자 chdir()이 맞을까?
	}
	return (output);
}

int	ft_write(int fd, void *buf, size_t byte)
{
	int	return_value;

	return_value = write(fd, buf, byte);
	if (return_value == -1)
		exitcode_with_err("write()", strerror(errno), 1);
	return (return_value);
}
