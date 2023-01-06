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

long long	ft_atoill(const char *str)
{
	unsigned long long	ret;
	unsigned long long	tmp;
	long long			check;
	int					sign;

	ret = 0;
	tmp = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1 - ((*str == '-') << 1);
	printf("sign %d\n",sign);
	str += (*str == '+' || *str == '-');
	while (*str >= '0' && *str <= '9')
	{
		tmp = ret * 10 + (*str - '0');
		if ((tmp - (*(str++) - '0')) / 10 == ret)
			ret = tmp;
		else
		{
			printf("else in \n");
			if (sign == 1)
				return (-1);
			else if (sign == -1)
				return (-1);
		}
		printf("ret %lld\n",ret);
		printf("tmp %lld\n",tmp);
	}
	return ((ret * sign));
}



void	ft_exit(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	g_exit_code = 0;
	ft_putendl_fd("exit", pipe_value->outfile_fd);
	if (cmd->cmd_argv[1] == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		exit(g_exit_code);
	}
	else if (cmd->cmd_argv[2] == NULL)
	{
		printf("ft_atoi === %d\n",ft_atoi(cmd->cmd_argv[1]));
		printf("ft_atoil === %lld\n",ft_atoill(cmd->cmd_argv[1]));
		g_exit_code = (unsigned char)ft_atoill(cmd->cmd_argv[1]);
		tcsetattr(STDIN_FILENO, TCSANOW, pipe_value->term);
		printf("in child - %d\n", g_exit_code);
		exit(g_exit_code);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
	}
}




// int	ft_exit_num_check(char *str)
// {
// 	long long	num;
// 	int			p_m;
// 	int			num_of_digits;

// 	num = 0;
// 	p_m = 1;
// 	num_of_digits = 0;
// 	while ((9 <= *str && *str <= 13) || *str == ' ')
// 		str++;
// 	if (*str == '-')
// 		p_m = -1;
// 	if (*str == '+' || *str == '-')
// 		str++;
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		num = num * 10 + (*str - '0');
// 		num_of_digits++;
// 		if (num < 0 || num_of_digits > 19)
// 			return (-1);
// 		str++;
// 	}
// 	return (num * p_m);
// }



// int	ft_exit_atoi(char *str)
// {
// 	long long	num;
// 	int			p_m;
// 	int			num_of_digits;

// 	num = 0;
// 	p_m = 1;
// 	num_of_digits = 0;
// 	while ((9 <= *str && *str <= 13) || *str == ' ')
// 		str++;
// 	if (*str == '-')
// 		p_m = -1;
// 	if (*str == '+' || *str == '-')
// 		str++;
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		num = num * 10 + (*str - '0');
// 		num_of_digits++;
// 		if (num < 0 || num_of_digits > 19)
// 			return (-1);
// 		str++;
// 	}
// 	return (num * p_m);
// }
