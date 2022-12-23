/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_linked_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:33:18 by kshim             #+#    #+#             */
/*   Updated: 2022/12/23 16:37:43 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOUBLY_LINKED_LIST_H
# define FT_DOUBLY_LINKED_LIST_H

typedef struct s_d_list
{
	void			*content;
	struct s_d_list	*prev;
	struct s_d_list	*next;
}				t_d_list;

typedef struct s_deque_tower
{
	t_d_list	*head;
	t_d_list	*tail;
}				t_detower;




typedef struct s_envp_content{
	char	*key;
	char	*value;
}	t_envp_content;





t_detower			*ft_dequetower(void);
t_d_list			*ft_d_lstnew(void *content);
void				ft_free_detower(t_detower **detower, void (*delete)(void *));
void				ft_d_lstclear(t_d_list **lst, void (*delete)(void *));
void				ft_d_lstdelone(t_d_list *lst, void (*delete)(void *));

void				ft_deque_add_back(t_detower *detower, t_d_list *new_elem);
void				ft_deque_add_front(t_detower *detower, t_d_list *new_elem);
void				ft_deque_del_back(t_detower *detower, void (*delete)(void *));
void				ft_deque_del_front(t_detower *detower, void (*delete)(void *));

void				ft_deque_add_prev_node(t_detower *detower, t_d_list *pos,
						t_d_list *new_elem);
void				ft_deque_add_next_node(t_detower *detower, t_d_list *pos,
						t_d_list *new_elem);

int					ft_deque_lstsize(t_detower *detower);


t_detower *ft_set_envp_dll(char **envp);
t_envp_content	*ft_set_envp_content(char *env);
char	**ft_set_char_envp_from_dll(t_detower *dll_envp_tower, char **old_mnsh_envp);
char	*ft_set_new_envp_string(t_d_list *lst_node);
void	ft_free_t_envp_content(void	*content);


void	test_print_dll_envp(t_detower *dll);

#endif