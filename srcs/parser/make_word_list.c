/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/19 17:32:36 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: segfaults on split_around when just \n is entered

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

// splits a word_list at whitespaces and returns the first element of the new list
// that list has been inserted into word_list
t_word_list	*split_element_at_wh(t_word_list **word_list, t_word_list *item)
{
	t_word_list	*tmp;

	item = remove_whitespace_element(word_list, item);
	if (!(item->word->flags & WM_SPLIT_AT_SPACES))
	{
		tmp = word_list_ft_split(item->word->word, item->word->flags);
		if (!tmp)
			return (free_word_list(word_list));
		tmp = wl_insert_instead(tmp, item);
		if (!tmp)
			return (free_word_list(word_list));
	}
	else
		tmp = item;
	return (tmp);
}

int	loop_to_split_on_spaces(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;
	t_word_list	*tmp;
	t_word_list	*first;

	(void)shell;
	curr = *word_list;
	while (curr)
	{
		ft_printf("\nProcessing current word: %s\n", curr->word->word);
		tmp = split_element_at_wh(word_list, curr);
		if (!tmp)
		{
            ft_printf("split_element_at_wh returned NULL\n");
			free_word_list(word_list);
			return (1);
		}
        ft_printf("After split - tmp points to: %s\n", tmp->word->word);
        ft_printf("Current list state:\n");
        ft_printf_word_list(*word_list);
		if (!(tmp->word->flags & W_EXPANDED))
		{
			curr = expand_and_split(word_list, first, shell);
			if (!curr)
			{
				free_word_list(word_list);
				return (1);
			}
			ft_printf("After expansion - curr points to: %s\n", curr->word->word);
			ft_printf_word_desc(curr->word);
		}
		else
			curr = tmp;
		curr = remove_whitespace_element(word_list, curr);
		if (!curr)
		{
            ft_printf("remove_whitespace_element returned NULL\n");
			free_word_list(word_list);
			return (1);
		}
		ft_printf("Before moving to next - curr points to: %s\n", curr->word->word);
        if (curr->next)
            ft_printf("Next word will be: %s\n", curr->next->word->word);
        else
            ft_printf("No next word\n");
		curr = curr->next;
		first = curr;
	}
    ft_printf("\nWORD LIST at the end of LOOP:\n");
    ft_printf_word_list(*word_list);
	return (0);
}

t_word_list	*expand_and_split(t_word_list **word_list, t_word_list *curr, t_shell *shell)
{
	int			expand_ret;
	t_word_list	*tmp;

	expand_ret = ft_expand_variable_name(curr->word, shell);
	if (expand_ret == 0)
	{
		free_word_list(word_list);
		return (NULL);
	}
	else if (expand_ret == -2)
		tmp = split_element_at_wh(word_list, curr);
	else
	{
		curr->word->flags |= W_EXPANDED;
		tmp = curr;
	}
	return (tmp);
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
