/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_expansion.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:59:04 by kshim             #+#    #+#             */
/*   Updated: 2022/12/28 14:01:31 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKEN_EXPANSION_H
# define FT_TOKEN_EXPANSION_H

int	ft_token_expansion(t_list *token_list, t_detower *dll_envp_tower);
int	ft_token_str_expansion(t_tkn *token, t_d_list *mnsh_envp);
int	ft_token_expand_expansion_sign(char **pos, char **ret_str, t_d_list *mnsh_envp);
int	ft_token_expand_double_quotes(char **pos, char **ret_str, t_d_list *mnsh_envp);
int	ft_token_expand_single_quotes(char **pos, char **ret_str);
int	ft_token_expand_str_control_with_expand(
	char **ret_str, char *start, int len, t_d_list *mnsh_envp);
int	ft_token_expand_str_control_without_expand(char **ret_str, char *start, int len);
char	*ft_compare_str_to_mnsh_envp_keys(char *str, t_d_list *mnsh_envp);

int	ft_token_is_expandable(t_list *token);

#endif