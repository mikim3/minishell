/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:02:05 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 12:15:17 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPE_H
# define FT_PIPE_H

typedef struct s_redirection_data
{
	int		pipe[2];
	int		infile_fd;
	int		outfile_fd;
	int		pre_pipe_read_end;
	int		pre_pipe_check;
	int		next_pipe_check;
	int		mnsh_builtin;
	int		in_redirected;
	int		out_redirected;
} 	t_pipe;

typedef enum e_pipe_end_name{
	P_READ = 0,
	P_WRITE
}	t_pipe_tag;

void	execute_fork(
		t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);

int	execute_redir(t_tree_node *node, t_pipe *m_pipe);
int	ft_redir_infile(char *file_name, t_pipe *m_pipe, int redir_fd);
int	ft_redir_outfile(char *file_name, t_pipe *m_pipe, int redir_fd);
int	ft_redir_append(char *file_name, t_pipe *m_pipe, int redir_fd);
int	ft_redir_here_doc(t_pipe *m_pipe, int redir_fd);

int	ft_redir_input_redirection(t_pipe *m_pipe, int file_fd, int redir_fd);
int	ft_redir_output_redirection(t_pipe *m_pipe, int file_fd, int redir_fd);

#endif