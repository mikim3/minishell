/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:16:16 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 18:21:44 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

static long long	ft_atoill(char *str, int *check)
{
	long long	ret;
	long long	tmp;
	int			sign;

	*check = FT_SUCCESS;
	ret = 0;
	tmp = 0;
	sign = 1;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '+' || *str == '-');
	while (*str >= '0' && *str <= '9')
	{
		tmp = ret * 10 + (*(str++) - '0');
		if (((ret > 0) && (tmp < 0)) || ((ret < 0) && (tmp > 0)))
		{
			printf("overflow \n");
			*check = FT_ERROR;
			return (-1);
		}
		ret = tmp;
	}
	if (*str && !(*str >= '0' && *str <= '9'))
		*check = FT_ERROR;
	return ((ret * sign));
}

void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	int	check;

	g_exit_code = 0;
	ft_putstr_fd("exit\n", pipe_value->outfile_fd);
	if (cmd->cmd_argv[1] == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		exit(g_exit_code);
	}
	else if (cmd->cmd_argv[2] == NULL)
	{
		g_exit_code = (unsigned char)ft_atoill(cmd->cmd_argv[1], &check);
		if (check == FT_ERROR)
			exitcode_with_err2("exit", cmd->cmd_argv[1], \
			"numeric argument required", 255);
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		exit(g_exit_code);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}
