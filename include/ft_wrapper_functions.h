/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapper_functions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:41:05 by kshim             #+#    #+#             */
/*   Updated: 2023/01/04 17:33:21 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_FUNCTIONS_H
# define FT_ERROR_FUNCTIONS_H

#include <sys/stat.h>
#include <fcntl.h>

int	ft_open(const char *str, int flags, mode_t mode);
int	ft_close(int fd);
pid_t ft_fork(void);
pid_t ft_pipe(int fd[2]);
int	ft_dup2(int oldfd, int newfd);
int	ft_access(const char *file, int flags);
int ft_fstat(int fd, struct stat *buf);

#endif