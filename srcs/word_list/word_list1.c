/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/12 15:02:47 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*make_word_list(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = init_word_list(line);
	word_list = (split_around(word_list_head->word));
	free_word_list(&word_list_head);
	if (!word_list || !word_list->word)
		return (NULL);
	if (loop_on_word_list(word_list))
		return (NULL);
	assign_flag(word_list);
	if (loop_to_split_on_spaces(word_list))
		return (NULL);
	return (word_list);
}

int	loop_to_split_on_spaces(t_word_list *word_list)
{
	t_word_list	*curr;
	t_word_list	*tmp;

	curr = word_list;
	while (curr)
	{
		if (!(curr->word->flags & WM_SPLIT_AT_SPACES))
		{
			tmp = word_list_ft_split(curr->word->word);
			// ft_printf("TMP:\n");
			// ft_printf_word_list(tmp);
			tmp = wl_insert_word_list(tmp, curr);
			// ft_printf("new last:\n");
			// ft_printf_word_desc(tmp->word);
			// ft_printf("curr to remove:\n");
			// ft_printf_word_desc(curr->word);
			word_list_delone(&word_list, curr);
			curr = tmp;
		}
		curr = curr->next;
	}
	return (0);
}

int	loop_on_word_list(t_word_list *word_list)
{
	t_word_list	*curr;

	curr = word_list;
	while (curr)
	{
		if (identify_word_type(curr->word))
		{
			if (!flag_correctly_delimeted(curr->word))
			{
				// ft_printf("debug print: not flag_correctly_delimeted\n");
				// ft_printf("-----------------------------------------\n");
				// ft_printf("-%s-\n", curr->word->word);
				// ft_printf("-----------------------------------------\n");
				return (syntax_error(word_list, curr->word->word));
			}
		remove_quotes(curr->word);
		}
		clean_whitespaces_to_space(curr->word);
		curr = curr->next;
	}
	return (0);
}

// returns head, and if head NULL, error occured and list was freed.
// puts string with size inside t_word_desc and adds that to the end of the list
t_word_list	*wordlist_from_line(t_word_list *h, char *line, int size, int flag)
{
	t_word_list	*item;
	t_word_desc	*desc;

	desc = make_word(line, size, flag);
	if (!desc)
		return (NULL);
	item = word_list_addback(h, desc);
	if (!item)
		free_word_list(&h);
	return (h);
}
