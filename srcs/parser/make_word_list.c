/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:31:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 15:41:23 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	loop_to_split_on_spaces(t_word_list **word_list, t_shell *shell)
{
	t_word_list	*curr;
	t_word_list	*tmp;
	int			tmp_expand_var_output;

	curr = *word_list;
	while (curr)
	{
		curr = remove_whitespace_element(word_list, curr);
		if (!(curr->word->flags & WM_SPLIT_AT_SPACES))
		{
			tmp = word_list_ft_split(curr->word->word);
			if (!tmp)
			{
				free_word_list(word_list);
				return (1);
			}
			tmp = wl_insert_word_list(tmp, curr);
			wl_delone(word_list, curr);
			curr = tmp;
		}
		tmp_expand_var_output = ft_expand_variable_name(curr->word, shell);
		ft_printf("output from tmp_expand_var_output:%d\n", tmp_expand_var_output);
		ft_printf_word_desc(curr->word);
		// not needed, already removing the unneccessary whitespace:
		// wd_remove_whitespace(curr->word);
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
