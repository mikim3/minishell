/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:59:04 by kshim             #+#    #+#             */
/*   Updated: 2023/01/03 09:47:24 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_EXPANSION_H
# define FT_TOKEN_EXPANSION_H

typedef enum e_expansion_mode{
	EXPAND_ALL = 0,
	EXPAND_QUOTE_ONLY,
	EXPAND_ENV_ONLY,
	EXPAND_D_QUOTE_WITH_ENV,
	EXPAND_D_QUOTE_WITHOUT_ENV,
	EXPAND_NOT
}	t_expand_mode;

int	ft_here_doc_expansion(t_list *token_list, t_detower *dll_envp_tower);
int	ft_write_here_doc_with_expand_mode(char *token_str, t_detower *dll_envp_tower, int is_env_expand);
void	ft_free_here_doc_memory(char *delimiter, char *buffer);

int	ft_token_expansion(t_list *token_list, t_detower *dll_envp_tower);
int	ft_token_str_expansion(char **token_str, t_d_list *mnsh_envp, int expand_mode);
int	ft_token_expand_expansion_sign(char **pos, char **ret_str, t_d_list *mnsh_envp);
int	ft_token_expand_double_quotes(char **pos, char **ret_str, t_d_list *mnsh_envp, int expand_mode);
int	ft_token_expand_single_quotes(char **pos, char **ret_str);
int	ft_token_expand_str_control_with_expand(
	char **ret_str, char *start, int len, t_d_list *mnsh_envp);
int	ft_token_expand_str_control_without_expand(char **ret_str, char *start, int len);
char	*ft_compare_str_to_mnsh_envp_keys(char *str, t_d_list *mnsh_envp);

int	ft_token_is_expandable(t_list *token);
int	ft_token_check_for_quote(t_list *token);

char *get_next_line(int fd);
#endif