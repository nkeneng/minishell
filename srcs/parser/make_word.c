/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  wd_wd_make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:44:21 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/13 12:45:26 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*make_word_list(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;

	word_list_head = wl_init(line);
	word_list = (split_around(word_list_head->word));
	free_word_list(&word_list_head);
	if (!word_list || !word_list->word)
		return (NULL);
	if (loop_on_word_list(word_list))
		return (NULL);
	assign_flag(word_list);
	if (!loop_to_split_on_spaces(&word_list))
		return (NULL);
	return (word_list);
}

int	loop_to_split_on_spaces(t_word_list **word_list)
{
	t_word_list	*curr;
	t_word_list	*tmp;

	curr = *word_list;
	while (curr)
	{
		if (!(curr->word->flags & WM_SPLIT_AT_SPACES))
		{
			tmp = word_list_ft_split(curr->word->word);
			if (!tmp)
			{
				free_word_list(word_list);
				return (0);
			}
			tmp = wl_insert_word_list(tmp, curr);
			wl_delone(word_list, curr);
			curr = tmp;
		}
		curr = curr->next;
	}
	return (1);
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
		ft_printf("removed_quotes\n");
		ft_printf_word_desc(curr->word);
		}
		clean_whitespaces_to_space(curr->word);
		ft_printf("cleaned_whitespaces\n");
		ft_printf_word_desc(curr->word);
		curr = curr->next;
	}
	return (0);
}