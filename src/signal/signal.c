/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:24:01 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 13:19:48 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == SIG_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == SIG_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == SIG_HANDLER)
		signal(SIGINT, signal_handler);
	if (sig_quit == SIG_IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == SIG_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == SIG_HANDLER)
		signal(SIGQUIT, signal_handler);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// backup
// void	wait_child(void)
// {
// 	int		status;
// 	int		signo;
// 	int		repeat;
// 	int		fix_g_exit_code;

// 	repeat = 0;
// 	while (wait(&status) != -1)
// 	{	
// 		printf("int status - %d\n", status);
// 		if (WIFSIGNALED(status))
// 		{
// 			signo = WTERMSIG(status);
// 			if (signo == SIGINT && repeat++ == 0)
// 				ft_putstr_fd("^C\n", STDERR_FILENO);
// 			else if (signo == SIGQUIT && repeat++ == 0)
// 				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
// 			g_exit_code = 128 + signo;
// 		}
// 		else// 현재는 가장 마지막에 들어온 녀석의 g_exit_code를 저장하지만 
// 		{
// 			printf("g_exit_code in else ===  %d\n", g_exit_code);
// 			if (repeat++ == 0)
// 				fix_g_exit_code = WEXITSTATUS(status);
// 		}
// 		printf("g_exit_code - %d\n", g_exit_code);
// 	}
// 	g_exit_code = fix_g_exit_code;
// 	set_signal(SIG_HANDLER, SIG_IGNORE);
//

void	wait_child(t_exec_fork *exec_data)
{
	pid_t	wait_pid;
	int		sig_status;
	int		signo;
	int		fix_g_exit_code;

	wait_pid = wait(&exec_data->status);
	sig_status = exec_data->status;
	printf("int status - %d\n", exec_data->status);
	if (WIFSIGNALED(sig_status))
	{
		signo = WTERMSIG(sig_status);
		if (signo == SIGINT && exec_data->repeat++ == 0)
			ft_putstr_fd("^C\n", STDERR_FILENO);
		else if (signo == SIGQUIT && exec_data->repeat++ == 0)
			ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
		if (wait_pid == exec_data->pid)
			g_exit_code = 128 + signo;
	}
	else
	{
		if (wait_pid == exec_data->pid)
			g_exit_code = exec_data->status;
	}
	set_signal(SIG_HANDLER, SIG_IGNORE);
}
