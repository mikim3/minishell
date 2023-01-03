/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/03 16:47:58 by kshim            ###   ########.fr       */
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
#include <signal.h> // signal, 
#include <errno.h> // errno
#include <string.h> // strerror() 
#include <stdio.h>
#include <readline/readline.h> // readline, rl_replace_line, rl_on_new_line, rl_redisplay
#include <readline/history.h> // add_history
#include <term.h>

#define SHELL_NAME "BABYSHELL"

typedef enum e_pwd_set{
	PWD_SET = 0,
	OLDPWD_SET
}		t_pwd_set;

typedef enum e_signal{
	SIG_IGNORE = 0,
	SIG_DEFAULT,
	SIG_HANDLER,
	SIG_CHILD_HANDLER
}		t_signal;

int g_exit_code;  //  $? 종료상태 코드 

/*
	builtin
*/
void	ft_cd(t_tree_cmd *cmd,t_detower *env_tower);
void	ft_echo(t_tree_cmd	*cmd, t_pipe	*pipe_value);
void	ft_env(t_detower	*env, t_pipe	*pipe_value);
void	ft_pwd(t_pipe	*pipe_value);
void	ft_exit(t_tree_cmd	*cmd, t_pipe	*pipe_value);
void	ft_export(t_tree_cmd	*cmd, t_detower	*env, t_pipe	*pipe_value);
char	*show_env_in_export(t_d_list	*env);
int			div_key_value(char *arg, char **key, char **value);
t_envp_content	*find_env_keycmp(t_d_list *env, char *env_key);

void	ft_unset(t_tree_cmd *cmd, t_detower *env);
void    unset_env(t_detower *env_tower,char *key);
void	delete_t_d_list(t_detower *env_tower, t_d_list	*env, t_d_list	*prev);
void	free_env_list(t_d_list **target);


/*
	env
*/

void	change_pwd_oldpwd(t_detower *env_tower,char *select);

int				check_env_key(char *key);
int				available_character(char *str);
void			env_key_error(char *cmd_name, char *key);

void			set_env(t_detower *env_tower, char *key, char *value);
void			set_new_env(t_detower	**env_tower, char	*key, char	*value);
void			set_env_value(t_envp_content *env, char *key, char *value);
t_envp_content	*env_new(void);

/*
	execute
*/

void 	execute_cmd(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);
// void	execute_fork(t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);
int		is_built_in(t_tree_cmd *cmd);
void	execute_builtin(t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe, int from_mnsh);
char	**get_env_path(t_detower *dll_envp_tower);
void	double_char_free(char **double_char);
char	*get_file_path_from_env_path(char *command,t_detower *dll_envp_tower);
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

// error.c
void    print_err(char *msg,int exit_code);




// main.c
void	main_init(int argc, char *argv[]);
void	init_pipe(t_pipe *m_pipe);
void	exe_cmd_set(t_tree_node *node);


/*
	signal.c
*/

void	set_signal(int sig_int, int sig_quit);
void	signal_handler(int signo);
void	signal_handler2(int signo);

/*
	utils
*/

void	ft_execve(const char *file, char *const *argv, char *const *envp);
void    exit_with_err(char *str, char *str_error, int exit_code);

#endif