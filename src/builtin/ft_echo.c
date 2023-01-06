/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:15:08 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/04 13:31:46 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_minishell.h"

static int	ft_strcmp_option_check(char *s1)
{
	size_t	i;

	i = 0;
	if (s1[i] != '-')
		return (0);
	if (s1[1])
		i++;
	else
		return (0);
	while (i < ft_strlen(s1))
	{
		if (s1[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	use_u_option_check(t_tree_cmd *cmd, int *no_option_index)
{
	int	index;
	int	use_u_option_check;

	index = 0;
	use_u_option_check = 0;
	while (cmd->cmd_argv[++index])
	{
		if ((ft_strcmp_option_check(cmd->cmd_argv[index]) == 1))
			use_u_option_check = 1;
		else
			break ;
	}
	*no_option_index = index;
	return (use_u_option_check);
}

void	ft_echo(t_tree_cmd *cmd, t_pipe *pipe_value)
{
	char	*output;
	int		index;
	int		use_u_option;
	int		argv_start_str;

	index = 0;
	argv_start_str = 0;
	use_u_option = use_u_option_check(cmd, &(argv_start_str));
	output = NULL;
	index = argv_start_str;
	while (cmd->cmd_argv[index])
	{
		output = ft_strjoin_infree(output, ft_strdup(cmd->cmd_argv[index]));
		if (cmd->cmd_argv[index + 1])
			output = ft_strjoin_infree(output, ft_strdup(" "));
		index++;
	}
	if (output != NULL)
		write(pipe_value->outfile_fd, output, ft_strlen(output));
	if (!use_u_option)
		write(pipe_value->outfile_fd, "\n", 1);
	free(output);
}
