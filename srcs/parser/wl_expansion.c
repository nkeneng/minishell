/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wl_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:06:21 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/11 11:43:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//function returns last element of list that was inserted instead of word,
//if curr was expanded
//or curr if not expanded
//or next element if curr was deleted because it got expanded to empty string
// t_word_list	*expand_and_split(t_word_list **word_list, t_word_list *curr, t_shell *shell)
// {
// 	int			expand_ret;
//
// 	expand_ret = ft_expand_variable_name(curr->word, shell);
// 	if (expand_ret == 0)
// 	{
// 		free_word_list(word_list);
// 		return (NULL);
// 	}
// 	else if (expand_ret == -2)
// 		curr = split_element_at_wh(word_list, curr);
// 	else if (expand_ret == -3)
// 		curr = wl_delone(word_list, curr);
// 	if (!curr)
// 		return (NULL);
// 	return (curr);
// }

// expands all variables in the word_list
t_word_list	*expand_and_split(t_word_list **word_list, t_word_list *curr, t_shell *shell)
{
	if (!wd_expand_var(&curr->word, shell))
	{
		free_word_list(word_list);
		return (NULL);
	}
	if (!curr->word->word)
		curr = wl_delone(word_list, curr);
	else if (curr->word->flags & W_EXPANDED)
		curr = split_element_at_wh(word_list, curr);
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

	curr = *word_list;
	while (curr)
	{
		ft_printf_word_desc(curr->word);
		while (contains_more_vars(curr->word))
		{
			if (!(curr->word->flags & W_EXPANDED))
				curr = expand_and_split(word_list, curr, shell);
			if (!curr)
				return (2);
			curr = wl_remove_whitespace_element(word_list, curr);
			if (!curr)
			{
				free_word_list(word_list);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}
