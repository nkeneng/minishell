/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 18:26:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_and_split(t_word_list **word_list, t_shell *shell);

// remove_whitespace_element and sets flags for previous item to have had space
t_word_list	*remove_whitespace_element(t_word_list **head, t_word_list *curr)
{
	int			i;

	i = ft_skip_whitespace(curr->word->word);
	if (i && curr->word->word[i] == '\0')
	{
		if (curr->prev)
			curr->prev->word->flags |= W_SPLITSPACE;
		curr = wl_delone(head, curr);
	}
	return (curr);
}

t_word_list	*make_word_list(char *line, t_shell *shell)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = wl_init(line);
	word_list = (split_around(word_list_head->word));
	free_word_list(&word_list_head);
	if (!word_list || !word_list->word)
		return (NULL);
	if (loop_on_word_list(&word_list))
		return (NULL);
	assign_flag(word_list);
	if (loop_to_split_on_spaces(&word_list, shell))
		return (NULL);
	return (word_list);
}

t_word_list	*split_element_at_wh(t_word_list **word_list, t_word_list *item)
{
	t_word_list	*tmp;

	item = remove_whitespace_element(word_list, item);
	if (!(item->word->flags & WM_SPLIT_AT_SPACES))
	{
		tmp = word_list_ft_split(item->word->word);
		if (!tmp)
			return (free_word_list(word_list));
		tmp = wl_insert_word_list(tmp, item);
		wl_delone(word_list, item);
		item = tmp;
	}
	item = item->next;
	return (item);
}


int	loop_to_split_on_spaces(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;

	curr = *word_list;
	while (curr)
	{
		curr = split_element_at_wh(word_list, curr);
		// curr = remove_whitespace_element(word_list, curr);
		// if (!(curr->word->flags & WM_SPLIT_AT_SPACES))
		// {
		// 	tmp = word_list_ft_split(curr->word->word);
		// 	if (!tmp)
		// 	{
		// 		free_word_list(word_list);
		// 		return (1);
		// 	}
		// 	tmp = wl_insert_word_list(tmp, curr);
		// 	wl_delone(word_list, curr);
		// 	curr = tmp;
		// }
		// curr = curr->next;
		expand_and_split(word_list, shell);
	}
	return (0);
}

int	expand_and_split(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;
	int			expand_ret;

	curr = *word_list;
	while (curr)
	{
		expand_ret = ft_expand_variable_name(curr->word, shell);
		if (expand_ret == 0)
		{
			free_word_list(word_list);
			return (1);
		}
		else if (expand_ret == -2)
			split_element_at_wh(word_list, curr);
		curr = curr->next;
	}
	return (0);
}

int	loop_on_word_list(t_word_list **word_list)
{
	t_word_list	*curr;

	curr = *word_list;
	while (curr)
	{
		if (identify_word_type(curr->word))
		{
			if (!flag_correctly_delimeted(curr->word))
				return (syntax_error(*word_list, curr->word->word));
			remove_quotes(curr->word);
		}
		curr = curr->next;
	}
	return (0);
}
