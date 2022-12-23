/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/23 18:32:15 by mikim3           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "../libft/libft.h"
#include "ft_tokenizer.h"
#include "ft_tree.h"
#include "ft_doubly_linked_list.h"

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>  //opendir, closedir, readdir
#include <term.h> // tgetstr, tgoto, tgetent, tgetflag, tgetnum, tputs
#include <sys/termios.h> //tcsetattr, tcgetattr
#include <signal.h> // signal, 
#include <errno.h> // errno

#include <readline/readline.h> // readline, rl_replace_line, rl_on_new_line, rl_redisplay
#include <readline/history.h> // add_history

#define SHELL_NAME "BABYSHELL"

int g_exit_code;  //  $? 종료상태 코드 

typedef struct s_pipe
{
    int     fd[2];
    int     infile_fd;
    int     outfile_fd;
} t_pipe;

typedef struct s_simple_cmd {
    char    *cmd_name;  // minishell $> export a=10 b=20  cmd->cmd == "export"
    char    *file_path;  //    ex) minishell > cd  -->  file_path == /usr/bin/cd
    char    **argv; // minishell $> export a=10 b=20 c=30  cmd->argv[0] == "export"  , argv[1] == "a=10" , argv[2] == "b=10"
}   t_simple_cmd;


typedef struct s_env
{
    // char    *original_text;  // ex) PATH=/Users/mikim3/brew/bin:/Users/mikim3/goinfre/brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
    char    *key; //  ex) PATH
    char    *value; //  ex) /Users/mikim3/brew/bin:/Users/mikim3/goinfre/brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
	struct s_env	*prev;
	struct s_env	*next;
}   t_env;

#endif