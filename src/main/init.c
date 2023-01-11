/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/11 17:30:17 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

void	init_pipe(t_pipe *m_pipe)
{
	m_pipe->next_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_check = BOOL_FALSE;
	m_pipe->pre_pipe_read_end = -1;
	m_pipe->infile_fd = STDIN_FILENO;
	m_pipe->outfile_fd = STDOUT_FILENO;
	m_pipe->mnsh_builtin = BOOL_FALSE;
	m_pipe->here_doc_opened = BOOL_FALSE;
	m_pipe->pipe_num = 0;
}

void	main_init(int argc, char **argv)
{
	struct termios	term;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(SIG_HANDLER, SIG_IGNORE);
	g_exit_code = 0;
}

void	term_init(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
