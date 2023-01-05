/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_parse_tree2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:24:51 by kshim             #+#    #+#             */
/*   Updated: 2023/01/05 16:25:10 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char **ft_set_cmd_argv(char ***argv, char *str)
{
	int		argv_size;
	char	**new_argv;
	int		i;

	if (str == 0 || ft_strcmp(str, "") == FT_SUCCESS)
		return (*argv);
	argv_size = 1;
	if (*argv != 0)
	{
		while ((*argv)[argv_size - 1] != 0)
			argv_size++;
	}
	new_argv = ft_calloc((argv_size + 1), sizeof(char *));
	if (new_argv == 0)
		return (0);
	new_argv[argv_size] = 0;
	new_argv[argv_size - 1] = ft_strdup(str);
	if (new_argv[argv_size - 1] == 0)
	{
		ft_free_string_ptr_arr(new_argv);
		return (0);
	}
	if (*argv == 0)
		return (new_argv);
	i = 0;
	while ((*argv)[i] != 0)
	{
		new_argv[i] = ft_strdup((*argv)[i]);
		if (new_argv[i] == 0)
		{
			ft_free_string_ptr_arr(new_argv);
			return (0);
		}
		i++;
	}
	ft_free_string_ptr_arr(*argv);
	return (new_argv);
}

void	ft_free_string_ptr_arr(char **argv)
{
	int	i;

	i = 0;
	if (argv == 0)
		return ;
	while (argv[i] != 0)
	{
		free(argv[i]);
		argv[i] = 0;
		i++;
	}
	free(argv);
	return ;
}
