/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:07:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/11 05:09:13 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

t_list		*ft_lstcreateaddback(t_list **lst, void *content);
void		ft_free_command(void *command);
int			ft_printf_lst(t_list *lst, int (*print)(void *));
int			ft_printf_command(void *command);

// conversion_wordlist_list.c
t_list		*convert_word_list_to_list(t_word_list *word_list);
t_list		*make_redirect_list(t_word_list **list);
t_word_list	*find_redir(t_word_list *list);
t_command	*make_command_list(t_word_list **word_list);
int			ft_printf_redirect(void *redirect);

// free_redirects.c
void		ft_lstfreeone(t_list **lst, t_list *deletee,
				void (*free_cont)(void *));
void		ft_free_redirect(void *redir);

void		ft_free_command_list(t_list **lst);
#endif //! LIST_H
