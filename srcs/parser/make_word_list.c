/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/20 11:16:31 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*make_word_list(char *line, t_shell *shell)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = wl_init(line);
	if (!word_list_head)
		return (NULL);
	word_list = (split_around(word_list_head->word));
	free_word_list(&word_list_head);
	if (!word_list || !word_list->word)
		return (NULL);
	if (wl_identify_words(&word_list))
		return (NULL);
	assign_flag(word_list);
	if (wl_split_on_whitesp(&word_list, shell))
		return (NULL);
	if (1 == wl_expand_list(&word_list, shell))
		return (NULL);
	return (word_list);
}

// splits a word_list at whitespaces and returns the last element 
// of the new list
// that list has been inserted into word_list
t_word_list	*split_element_at_wh(t_word_list **word_list, t_word_list *item)
{
	t_word_list	*tmp;

	item = wl_remove_whitespace_element(word_list, item);
	if (!(item->word->flags & WM_SPLIT_AT_SPACES))
	{
		tmp = word_list_ft_split(item->word->word, item->word->flags);
		if (!tmp)
			return (free_word_list(word_list));
		// tmp = wl_insert_instead(tmp, item);
		tmp = wl_insert_word_list(tmp, item);
		wl_delone(word_list, item);
		item = tmp;
	}
	return (item);
}

//splits at whitespaces
int	wl_split_on_whitesp(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;

	(void)shell;
	curr = *word_list;
	while (curr)
	{
		curr = split_element_at_wh(word_list, curr);
		if (!curr)
		{
			free_word_list(word_list);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	wl_identify_words(t_word_list **word_list)
{
	t_word_list	*curr;

	curr = *word_list;
	while (curr)
	{
		if (identify_word_type(curr->word))
		{
			if (!flag_correctly_delimeted(curr->word))
				return (syntax_error(word_list, curr->word->word));
			remove_quotes(curr->word);
		}
		curr = curr->next;
	}
	return (0);
}
