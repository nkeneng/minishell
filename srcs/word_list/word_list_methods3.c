/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/12 19:26:32 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns head, and if head NULL, error occured and list was freed.
// puts string with size inside t_word_desc and adds that to the end of the list
t_word_list	*wl_from_line(t_word_list *h, char *line, int size, int flag)
{
	t_word_list	*item;
	t_word_desc	*desc;

	desc = wd_make_word(line, size, flag);
	if (!desc)
		return (NULL);
	item = wl_addback(h, desc);
	if (!item)
		free_word_list(&h);
	return (h);
}
