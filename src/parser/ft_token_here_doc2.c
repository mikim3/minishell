/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_here_doc2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:22:03 by kshim             #+#    #+#             */
/*   Updated: 2023/01/11 19:14:53 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

int	ft_make_h_doc_set_before_loop(char *token_str, char **delimiter, \
	int *here_doc_fd, int pipe_num)
{
	char	*f_name;

	*here_doc_fd = -1;
	f_name = ft_make_h_doc_file_name(pipe_num);
	if (f_name == 0)
		return (FT_ERROR);
	*here_doc_fd = ft_open(f_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(f_name);
	if (*here_doc_fd == -1)
		return (FT_ERROR);
	*delimiter = ft_strjoin(token_str, "\n");
	if (*delimiter == 0)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

char	*ft_make_h_doc_file_name(int pipe_num)
{
	char	*tmp;
	char	*ret;

	tmp = ft_itoa(pipe_num);
	if (tmp == 0)
		return (0);
	ret = ft_strjoin("/tmp/.mnsh_here_doc", tmp);
	free(tmp);
	if (ret == 0)
		return (0);
	tmp = ret;
	ret = ft_strjoin(tmp, ".tmp");
	free(tmp);
	if (ret == 0)
		return (0);
	return (ret);
}

int	ft_make_h_doc_loop(char *delimiter, \
	int here_doc_fd, t_detower *dll_envp_tower, int is_env_expand)
{
	char	*buffer;
	char	*tmp_buf;
	int		here_doc_stop;

	here_doc_stop = BOOL_FALSE;
	if (ft_make_h_doc_readline(&tmp_buf, &here_doc_stop) == FT_ERROR)
		return (FT_ERROR);
	if (here_doc_stop == BOOL_TRUE)
		return (free(tmp_buf), FT_SUCCESS);
	buffer = ft_strjoin(tmp_buf, "\n");
	free(tmp_buf);
	if (buffer == 0)
		return (FT_ERROR);
	if (ft_strcmp(buffer, delimiter) == 0)
		return (free(buffer), FT_SUCCESS);
	if (is_env_expand == BOOL_TRUE)
	{
		if (ft_token_str_expansion(&buffer, \
			dll_envp_tower->head, EXPAND_ENV_ONLY) == FT_ERROR)
			return (free(buffer), FT_ERROR);
	}
	if (write(here_doc_fd, buffer, ft_strlen(buffer)) < 0)
		return (free(buffer), FT_ERROR);
	return (free(buffer), -1);
}

int	ft_make_h_doc_readline(char **buffer, int *here_doc_stop)
{
	int	org_exit_code;
	int	ret;
	int	tmp_fd;

	org_exit_code = g_exit_code;
	g_exit_code = 0;
	tmp_fd = dup(STDIN_FILENO);
	ret = FT_SUCCESS;
	*buffer = readline("> ");
	if (*buffer == 0)
		ret = ft_make_h_doc_readline_eof_condition(\
				here_doc_stop, &org_exit_code, tmp_fd);
	g_exit_code = org_exit_code;
	return (ret);
}

int	ft_make_h_doc_readline_eof_condition(int *here_doc_stop, \
	int *org_exit_code, int tmp_fd)
{
	if (g_exit_code == 0)
	{
		*here_doc_stop = BOOL_TRUE;
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[2C", STDOUT_FILENO);
		return (FT_SUCCESS);
	}
	else if (g_exit_code == 1)
	{
		*org_exit_code = 1;
		dup2(tmp_fd, STDIN_FILENO);
		close(tmp_fd);
		return (FT_ERROR);
	}
	return (FT_ERROR);
}
