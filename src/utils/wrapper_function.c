/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 14:25:55 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	ft_execve(char *file, char **argv, char **envp)
{
	if (execve(file, argv, envp) == -1)
	{
		if (ft_strncmp(argv[0], "/", 1) == 0 || \
			ft_strncmp(argv[0], "./", 2) == 0)
		{
			if (errno == ENOENT)
				exitcode_with_err(argv[0], strerror(errno), 127);
			else if (errno == EACCES)
				exitcode_with_err(argv[0], strerror(errno), 126);
			else
				exitcode_with_err(argv[0], strerror(errno), 1);
		}
		else
			exitcode_with_err(argv[0], "command not found", 127);
	}
	return ;
}

int	ft_chdir(char *dir)
{
	int		return_value;

	return_value = chdir(dir);
	if (return_value == -1)
	{
		if (errno == ENOENT)
			exitcode_with_err("cd", strerror(errno), 127);
		else if (errno == EACCES)
			exitcode_with_err("cd", strerror(errno), 126);
		else
			exitcode_with_err("cd", strerror(errno), 1);
	}
	return (return_value);
}

char	*ft_getcwd(char *buf, size_t size)
{
	char	*output;

	output = getcwd(buf, size);
	if (output == NULL)
		exitcode_with_err("getcwd()", strerror(errno), 1);
	return (output);
}

char	*ft_getenv(char *path_name)
{
	char	*output;

	output = getenv(path_name);
	if (output == NULL)
		exitcode_with_err("getenv()", strerror(errno), 1);
	return (output);
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

int	ft_fstat(int fd, struct stat *buf)
{
	int	ret_val;

	ret_val = fstat(
			fd, buf);
	if (ret_val == -1)
		exitcode_with_err("fstat()", strerror(errno), 1);
	return (ret_val);
}
