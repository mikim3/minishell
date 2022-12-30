/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2022/12/30 14:41:11 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "../libft/libft.h"
#include "ft_tokenizer.h"
#include "ft_tree.h"
#include "ft_doubly_linked_list.h"
#include "ft_token_expansion.h"
#include "ft_pipe.h"

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>  //opendir, closedir, readdir
#include <term.h> // tgetstr, tgoto, tgetent, tgetflag, tgetnum, tputs
#include <sys/termios.h> //tcsetattr, tcgetattr
#include <signal.h> // signal, 
#include <errno.h> // errno
#include <sys/stat.h>  //
#include <string.h> // strerror() 

#include <readline/readline.h> // readline, rl_replace_line, rl_on_new_line, rl_redisplay
#include <readline/history.h> // add_history

#define SHELL_NAME "BABYSHELL"

int g_exit_code;  //  $? 종료상태 코드 

/*
typedef struct s_pipe
{
	int		fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		next_pipe_check;	// next_pipe_check 
	int		pre_pipe_check;		
	int		pipe_read_end;		// 처음에 STDIN_FILENO로시작 // pipe_read_end인 4
	int		pipe_write_end;		// 처음에 STDOUT_FILENO로시작 // 
} 	t_pipe;
*/

// typedef struct s_exe_cmd {
//     char    *cmd_name;  // minishell $> export a=10 b=20  t_exe_cmd->cmd_name == "export"
//     char    *file_path;  //    ex) minishell > cd  -->  file_path == /usr/bin/cd
//     char    **argv; // minishell $> export a=10 b=20 c=30  t_exe_cmd->argv[0] == "export"  , argv[1] == "a=10" , argv[2] == "b=10"
// }   t_exe_cmd;

// typedef struct s_env
// {
//     // char    *original_text;  // ex) PATH=/Users/mikim3/brew/bin:/Users/mikim3/goinfre/brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
//     char    *key; //  ex) PATH
//     char    *value; //  ex) /Users/mikim3/brew/bin:/Users/mikim3/goinfre/brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki 
// 	struct s_env	*prev;
// 	struct s_env	*next;
// }   t_env;

/*
	builtin
*/

void	ft_cd(t_tree_cmd *cmd, t_pipe *pipe_value);
void	ft_echo(t_tree_cmd *cmd, t_pipe *pipe_value);
void	ft_pwd(t_tree_cmd *cmd, t_pipe *pipe_value);



/*
	env
*/


/*
	execute
*/

void 	execute_cmd(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);
// void	execute_fork(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);
int		is_built_in(t_tree_cmd *cmd);
void	execute_builtin(t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe);
char	**get_env_path(t_detower *dll_envp_tower);
void	double_char_free(char **double_char);
char	*get_file_path_from_env_path(char *command,t_detower *dll_envp_tower);
char	*get_current_path(void);
char	*set_file_path(char *command, t_detower *dll_envp_tower);
void	execute_external(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe);
int		execute_noprint_builtin(t_tree_cmd *cmd, t_detower *dll_envp_tower,t_pipe *m_pipe);
void	wait_child(void);
void    next_pipe_check(t_tree_node *node,t_pipe *m_pipe);
void    ft_execute_tree(t_tree_node *node, t_detower *dll_envp_tower, t_pipe *m_pipe);
void	init_pipe_in_execute(t_pipe *m_pipe);


int		ft_tree_node_pre_traversal2(t_tree_node *token_tree,t_detower *dll_envp_tower,t_pipe *m_pipe, void (*function)(t_tree_node *,t_detower *,t_pipe *));
int		ft_tree_node_pre_traversal_exe_cmd_set(t_tree_node *target_tree, char *input, void (*function)(void *, char *));

/*
	main

*/

void	main_init(void);
void	init_pipe(t_pipe *m_pipe);
void	exe_cmd_set(t_tree_node *node);


#endif