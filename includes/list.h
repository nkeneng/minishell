/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:07:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/06 10:08:24 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

t_list	*ft_lstcreateaddback(t_list **lst, void *content);
void	ft_free_command(void *command);
int		ft_printf_lst(t_list *lst, int (*print)(void*));
int		ft_printf_command(void *command);

// conversion_wordlist_list.c
t_list	*convert_word_list_to_list(t_word_list *word_list);
t_list	*make_redirect_list(t_word_list **list);
t_word_list	*find_redir(t_word_list *list);
t_command	*make_command_list(t_word_list *word_list, t_word_list *curr);
#endif //!LIST_H
