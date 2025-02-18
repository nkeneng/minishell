/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wl_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:06:21 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 12:10:58 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// expands all variables in the word_list
t_word_list	*expand_and_split(t_word_list **wl, t_word_list *curr, t_shell *sh)
{
	if (!wd_expand_var(&curr->word, sh))
	{
		free_word_list(wl);
		return (NULL);
	}
	if (!curr->word->word || curr->word->word[0] == '\0')
		return (curr);
	if (curr->word->flags & W_EXPANDED)
		curr = split_element_at_wh(wl, curr);
	if (!curr)
		return (NULL);
	return (curr);
}

// expands all variables in the word_list
// if a valiable is at the end at expanded to empty string it returns 2
// if a malloc error occurs it returns 1
// else returns 0
int	wl_expand_list(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;
	t_word_list	*next;

	curr = *word_list;
	while (curr)
	{
		next = curr->next;
		while (curr->word && contains_more_vars(curr->word))
		{
			if (!(curr->word->flags & W_EXPANDED))
				curr = expand_and_split(word_list, curr, shell);
			if (!curr)
				return (1);
		}
		curr = wl_remove_whitespace_element(word_list, curr);
		if (!curr && next)
		{
			free_word_list(word_list);
			return (1);
		}
		curr = next;
	}
	return (0);
}
