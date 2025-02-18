/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_methods2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:58:56 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 07:39:33 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Helper function to create and add a word node at the back,
// frees everything in case of error
t_word_list	*wl_add_node(t_word_list **head, char *line, int len, int flag)
{
	t_word_desc	*new_item;
	t_word_list	*new_node;

	if (len <= 0)
		return (*head);
	new_item = wd_make_word(line, len, flag);
	if (!new_item)
		return (free_word_list(head));
	new_node = wl_addback(*head, new_item);
	if (!new_node)
		return (free_word_list(head));
	if (!*head)
		*head = new_node;
	return (new_node);
}

// deletes a single word_list item and reconnects the list
// returns new current item
t_word_list	*wl_delone(t_word_list **head, t_word_list *to_remove)
{
	t_word_list	*next;

	if (!head || !to_remove)
		return (NULL);
	next = to_remove->next;
	if (*head == to_remove)
		*head = to_remove->next;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	if (to_remove->word)
		free_word_desc(&to_remove->word);
	free(to_remove);
	return (next);
}

// unused!!!
t_word_desc	*wl_unlink(t_word_list **head, t_word_list *to_unlink)
{
	t_word_desc	*word;

	word = to_unlink->word;
	if (!head || !to_unlink)
		return (NULL);
	if (to_unlink == *head)
		*head = to_unlink->next;
	if (to_unlink->prev)
		to_unlink->prev->next = to_unlink->next;
	if (to_unlink->next)
		to_unlink->next->prev = to_unlink->prev;
	free(to_unlink);
	return (word);
}

/**
 * @brief Converts a word list element to a redirect item and removes the 
 * element from the list.
 *
 * This function takes a word list element (`to_unlink`), creates a new 
 * redirect item (`t_redirect`) containing the word from `to_unlink`, and 
 * removes `to_unlink` from the word list. The word in `to_unlink` is moved 
 * to the new redirect item, and `to_unlink` is freed.
 *
 * @param head A pointer to the head of the word list.
 * @param to_unlink The word list element to be converted to a redirect item 
 * and removed from the list.
 * @return A pointer to the newly created redirect item, or NULL if an error 
 * occurs.
 */
t_redirect	*wl_to_redirect(t_word_list **head, t_word_list *to_unlink)
{
	t_redirect	*redirect;

	if (!head || !to_unlink || !to_unlink->word)
		return (NULL);
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->filename = to_unlink->word;
	redirect->next = NULL;
	if (to_unlink == *head)
		*head = to_unlink->next;
	if (to_unlink->prev)
		to_unlink->prev->next = to_unlink->next;
	if (to_unlink->next)
		to_unlink->next->prev = to_unlink->prev;
	to_unlink->word = NULL;
	free(to_unlink);
	return (redirect);
}

// inserts a word list called new_lst instead of a word list element called old
//returns the last element of the inserted list
t_word_list	*wl_insert_instead(t_word_list *new_lst, t_word_list *old)
{
	t_word_list	*next_element;
	t_word_list	*last;

	if (!new_lst || !old)
		return (NULL);
	next_element = old->next;
	if (old->prev)
	{
		old->prev->next = new_lst;
		new_lst->prev = old->prev;
	}
	else
		new_lst->prev = NULL;
	last = new_lst;
	while (last->next)
		last = last->next;
	last->next = next_element;
	if (next_element)
		next_element->prev = last;
	free_word_desc(&old->word);
	free(old);
	return (last);
}
