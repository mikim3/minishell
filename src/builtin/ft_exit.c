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

static void	ft_atoill_numcheck(char *str, int *check)
{
	if (*str && !(*str >= '0' && *str <= '9'))
		*check = FT_ERROR;
}

static int	ft_atoill_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s1_uc;
	const unsigned char	*s2_uc;
	size_t				i;

	s1_uc = (const unsigned char *)s1;
	s2_uc = (const unsigned char *)s2;
	i = 0;
	// s1을 00은 무시하게 바꾸기 아니면 매커니즘 자체를 바꾸기 
	//  아니면 00은 제거 하고 문자열 돌려받고 시작하기
	while (s1_uc[i] && s2_uc[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1_uc[i] != s2_uc[i])
			break ;
		i++;
	}
	return ((int)(s1_uc[i] - s2_uc[i]));
}

static long long	ft_atoill(char *str, int *check)
{
	long long	ret;
	long long	tmp;
	int			sign;

	ret = 0;
	tmp = 0;
	sign = 1;
	if (!ft_atoill_strcmp(str, "-9223372036854775808"))
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1 - ((*str == '-') << 1);
	str += (*str == '+' || *str == '-');
	ft_atoill_numcheck(str, check);
	while (*str >= '0' && *str <= '9')
	{
		tmp = ret * 10 + (*(str++) - '0');
		if (((ret > 0) && (tmp < 0)) || ((ret < 0) && (tmp > 0)))
		{
			*check = FT_ERROR;
			return (-1);
		}
		ret = tmp;
	}
	return ((ret * sign));
}

void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	int	check;

	check = FT_SUCCESS;
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
