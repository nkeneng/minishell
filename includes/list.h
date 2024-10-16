/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:07:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 16:49:18 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

t_list	*ft_lstcreateaddback(t_list **lst, void *content);
void	ft_free_command(void *command);
int		ft_printf_lst(t_list *lst, int (*print)(void*));
int		ft_printf_command(void *command);

#endif //!LIST_H
