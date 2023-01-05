/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 17:51:38 by mikim3            #+#    #+#             */
/*   Updated: 2023/01/05 16:49:49 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "../libft/libft.h"
# include "ft_enum.h"
# include "ft_struct.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <sys/stat.h>
# include <fcntl.h>

# define SHELL_NAME "BABYSHELL"

int	g_exit_code;

/*
	ft_doubly_linked_list
*/

t_detower	*ft_dequetower(void);
t_d_list	*ft_d_lstnew(void *content);
void		ft_free_detower(t_detower **detower, void (*delete)(void *));
void		ft_d_lstclear(t_d_list **lst, void (*delete)(void *));
void		ft_d_lstdelone(t_d_list *lst, void (*delete)(void *));
void		ft_deque_add_back(t_detower *detower, t_d_list *new_elem);
void		ft_deque_add_front(t_detower *detower, t_d_list *new_elem);
void		ft_deque_del_back(t_detower *detower, void (*delete)(void *));
void		ft_deque_del_front(t_detower *detower, void (*delete)(void *));
void		ft_deque_add_prev_node(t_detower *detower, t_d_list *pos,
				t_d_list *new_elem);
void		ft_deque_add_next_node(t_detower *detower, t_d_list *pos,
				t_d_list *new_elem);
int			ft_deque_lstsize(t_detower *detower);
t_detower	*ft_set_envp_dll(char **envp);
t_detower	*ft_set_envp_dll_action(char **envp, t_detower *dll_envp_tower);
t_env_ctnt	*ft_set_envp_content(char *env);
int			ft_seperate_env_key_value(t_env_ctnt *content, char *env);
char		**ft_set_char_envp_from_dll(\
	t_detower *dll_envp_tower, char **old_mnsh_envp);
char		*ft_set_new_envp_string(t_d_list *lst_node);
void		ft_free_t_envp_content(void	*content);

/*
	ft_pipe
*/

void		execute_fork(t_tree_node *token_tree,
				t_detower *dll_envp_tower, t_pipe *m_pipe);

int			execute_redir(t_tree_node *node, t_pipe *m_pipe);
int			ft_match_redir_symbol(\
	char *redir, char *file_name, int redir_fd, t_pipe *m_pipe);
int			ft_redir_infile(char *file_name, t_pipe *m_pipe, int redir_fd);
int			ft_redir_outfile(char *file_name, t_pipe *m_pipe, int redir_fd);
int			ft_redir_append(char *file_name, t_pipe *m_pipe, int redir_fd);
int			ft_redir_here_doc(t_pipe *m_pipe, int redir_fd);
int			ft_redir_input_redirection(\
	t_pipe *m_pipe, int file_fd, int redir_fd);
int			ft_redir_output_redirection(\
	t_pipe *m_pipe, int file_fd, int redir_fd);

/*
	ft_token_expansion
*/

int			ft_here_doc_expansion(\
	t_list *token_list, t_detower *dll_envp_tower);
int			ft_check_here_doc(t_list **token_node, char *redir, \
	t_list *token_list, t_detower *dll_envp_tower);
int			ft_here_doc_with_delimiter_control(t_list **token_node, \
	t_list *token_list, t_detower *dll_envp_tower);
int			ft_make_h_doc_wth_expand(\
	char *token_str, t_detower *dll_envp_tower, int is_env_expand);
int			ft_make_h_doc_loop(char *delimiter, \
	int here_doc_fd, t_detower *dll_envp_tower, int is_env_expand);

int			ft_token_expansion(t_list *token_list, t_detower *dll_envp_tower);
int			ft_token_str_expansion(\
	char **token_str, t_d_list *mnsh_envp, int expand_mode);
int			ft_token_expand_expansion_sign(\
	char **pos, char **ret_str, t_d_list *mnsh_envp);
int			ft_token_expand_double_quotes(\
	char **pos, char **ret_str, t_d_list *mnsh_envp, int expand_mode);
int			ft_token_expand_single_quotes(char **pos, char **ret_str);
int			ft_token_expand_str_control_with_expand(
				char **ret_str, char *start, int len, t_d_list *mnsh_envp);
int			ft_token_expand_str_control_without_expand(\
	char **ret_str, char *start, int len);
char		*ft_compare_str_to_mnsh_envp_keys(char *str, t_d_list *mnsh_envp);

int			ft_token_is_expandable(t_list *token);
int			ft_token_check_for_quote(t_list *token);

/*
	ft_tokenizer
*/

void		*ft_tokenizer(char *str);
int			ft_initialize_tokenizer( t_tknizer *tknizer, char *str);
int			ft_tokenizing_loop(t_tknizer *tknizer, int error, int *prev_type);
int			ft_close_quote(t_tknizer *tknizer, int *prev_type);
int			ft_check_for_space(t_tknizer *tknizer, int error, int *prev_type);

int			ft_token_processor(t_tknizer *tknizer,
				int *prev_type);
int			ft_token_set(t_tknizer *tknizer, int type);
int			ft_token_cut(t_list **token_list, t_tkn *token);
t_tkn		*ft_new_token(void);
void		ft_token_start_set(t_tknizer *tknizer);

int			ft_is_quote(char cha);
int			ft_can_become_operator(char diff_target, char cha, int *oper_len);
int			ft_is_operator(char cha);

void		ft_free_tokenizer_list_and_token(\
	t_list **token_list, t_tkn **token, int procedure);
void		ft_free_a_token_list_content(void *target);

/*
	ft_syntax_analysis
*/

int			ft_syntax_analysis(t_list *token_list);

int			ft_stx_a_pipeline(t_list *token_list, t_list *token, int token_pos);
int			ft_stx_a_simple_cmd(\
	t_list *token_list, t_list *token, int token_pos);

int			ft_stx_a_word_and_cmd_suffix_case(\
	t_list *token_list, t_list *token, int token_pos);

int			ft_stx_a_cmd_prefix(\
	t_list *token_list, t_list *token, int token_pos);
int			ft_stx_a_cmd_suffix(\
	t_list *token_list, t_list *token, int token_pos);
int			ft_stx_a_redir(t_list *token_list, t_list *token, int token_pos);
int			ft_stx_a_word(t_list *token_list, t_list *token, int token_pos);

int			ft_token_type(t_list *token);
char		*ft_token_str(t_list *token);

/*
	ft_tree
*/

t_tree_node	*ft_tree_init(int type, void *node_content);
int			ft_tree_node_pre_traversal(\
	t_tree_node *target_tree, void (*function)(void *));
int			ft_tree_node_post_traversal(\
	t_tree_node *target_tree, void (*function)(void *));

/*
	ft_syntax_parse_tree
*/

t_tree_node	*ft_syntax_parse_tree(t_list *token_list);
int			ft_syntax_parse_pipeline(t_list *token, t_tree_node **parse);
int			ft_syntax_parse_pipeline_data(t_tree_node **parse, \
	t_tree_node **recur_parse, t_tree_node **cur_redirects, \
	t_tree_node **simple_cmd);
int			ft_syntax_parse_token_traversal(int *token_type, t_list **token, \
	t_tree_node *cur_redirects, t_tree_node *simple_cmd);

int			ft_syntax_parse_redirections(\
	t_list **token, t_tree_node *cur_redirects, int token_type);
t_tree_rdr	*ft_node_content_redir(t_list **token);

int			ft_syntax_parse_cmd(t_list **token, t_tree_node *cmd);
char		**ft_set_cmd_argv(char ***argv, char *str);
char		**ft_set_cmd_argv_set_new_argv(char ***argv, char *str);

void		ft_free_string_ptr_arr(char **argv);

void		ft_free_a_tree_node(void *target);
void		ft_free_a_tree_node_content(t_tree_node *node);

/*
	ft_wrapper_functions
*/

int			ft_open(const char *str, int flags, mode_t mode);
int			ft_close(int fd);
pid_t		ft_fork(void);
pid_t		ft_pipe(int fd[2]);
int			ft_dup2(int oldfd, int newfd);
int			ft_access(const char *file, int flags);
int			ft_fstat(int fd, struct stat *buf);

/*
	builtin
*/
void		ft_cd(t_tree_cmd *cmd, t_detower *env_tower);
void		ft_echo(t_tree_cmd	*cmd, t_pipe	*pipe_value);
void		ft_env(t_detower	*env, t_pipe	*pipe_value);
void		ft_pwd(t_pipe	*pipe_value);
void		ft_exit(t_tree_cmd	*cmd, t_pipe	*pipe_value);
void		ft_export(t_tree_cmd	*cmd, \
t_detower	*env, t_pipe	*pipe_value);
int			div_key_value(char *arg, char **key, char **value);
t_env_ctnt	*find_env_keycmp(t_d_list *env, char *env_key);

void		ft_unset(t_tree_cmd *cmd, t_detower *env);
void		unset_env(t_detower *env_tower, char *key);
void		delete_t_d_list(t_detower *env_tower, \
t_d_list	*env, t_d_list	*prev);
void		free_env_list(t_d_list **target);

/*
	env
*/

void		change_pwd(t_detower *env_tower, char *select);
void		change_oldpwd(t_detower *env_tower, char *select);

int			check_env_key(char *key);
int			available_character(char *str);
void		env_key_error(char *cmd_name, char *key);

void		set_env(t_detower *env_tower, char *key, char *value);
void		set_new_env(t_detower	**env_tower, char	*key, char	*value);
void		set_env_value(t_env_ctnt *env, char *key, char *value);
t_env_ctnt	*env_new(void);

/*
	execute
*/

void		execute_cmd(\
	t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);

void		fork_routine(t_tree_node *pipeline, \
	t_pipe *m_pipe, int *iter, t_detower *dll_envp_tower);
int			fork_action(t_pipe *m_pipe, \
	t_tree_node *pipeline, t_detower *dll_envp_tower);
void		parent_routine(t_pipe	*m_pipe);
void		child_routine(t_pipe *m_pipe, \
	t_tree_node *pipeline, t_detower *dll_envp_tower);

int			is_built_in(t_tree_cmd *cmd);
void		execute_builtin(\
	t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe);
char		**get_env_path(t_detower *dll_envp_tower);
void		double_char_free(char **double_char);
char		*get_file_path_from_env_path(\
	char *command, t_detower *dll_envp_tower);
char		*set_file_path(char *command, t_detower *dll_envp_tower);
void		execute_external(\
	t_tree_node *token_tree, t_detower *dll_envp_tower, t_pipe *m_pipe);
int			execute_noprint_builtin(\
	t_tree_cmd *cmd, t_detower *dll_envp_tower, t_pipe *m_pipe);
void		wait_child(void);
int			next_pipe_check(t_tree_node *node, t_pipe *m_pipe);
void		ft_execute_tree(\
	t_tree_node *node, t_detower *dll_envp_tower, t_pipe *m_pipe);

int			ft_tree_node_pre_traversal2(t_tree_node *token_tree, \
	t_detower *dll_envp_tower, \
	t_pipe *m_pipe, void (*function)(t_tree_node *, t_detower *, t_pipe *));
int			ft_tree_node_pre_traversal_exe_cmd_set(\
	t_tree_node *target_tree, char *input, void (*function)(void *, char *));

/*
	main
*/

// error.c
void		print_err(char *msg, int exit_code);

// main.c
void		main_init(int argc, char *argv[]);
void		init_pipe(t_pipe *m_pipe);
char		*ft_readline(char *prompt);
void		main_loop(t_list *token_list, t_detower *dll_envp_tower, \
	t_tree_node *token_tree);

/*
	signal.c
*/

void		set_signal(int sig_int, int sig_quit);
void		signal_handler(int signo);
void		signal_handler2(int signo);

/*
	utils
*/

void		ft_execve(char *file, char **argv, char **envp);
int			ft_chdir(char *dir);
void		exitcode_with_err(char *str, char *str_error, int exit_code);
char		*ft_getcwd(char *buf, size_t size);

#endif