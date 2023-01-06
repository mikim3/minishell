/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:24:01 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/06 21:50:32 by kshim            ###   ########.fr       */
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
	if (sig_int == SIG_HERE_DOC)
		signal(SIGINT, signal_handler_here_doc);
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

void	signal_handler_here_doc(int signo)
{
	extern int		rl_catch_signals;
	struct termios	org_term;
	struct termios	tmp_term;
	int				ch;

	ch = 0;
	rl_catch_signals = 0;
	if (signo == SIGINT)
	{
		tcgetattr(STDIN_FILENO, &org_term);
		tcgetattr(STDIN_FILENO, &tmp_term);
		tmp_term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp_term);
		g_exit_code = 1;
		ch = 4;
		write(0, &ch, sizeof(int));
		// readline 대기 멈추는 법
			// 이걸 호출한 readline에 eof를 주기?
				// 근데 이러면 error를 줄 수가 없음. 구분이 안된다.
				// 그럼 여기서 설정한 전역 변수를 이용해보자
					// -> 이러면 eof만 줄 수 있으면 됨
		tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
	}
}

void	wait_child(t_exec_fork *exec_data)
{
	pid_t	wait_pid;
	int		sig_status;
	int		signo;

	wait_pid = wait(&exec_data->status);
	sig_status = exec_data->status;
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
			g_exit_code = WEXITSTATUS(exec_data->status);
	}
	set_signal(SIG_HANDLER, SIG_IGNORE);
}
