/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:40:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/22 10:37:14 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*expand(t_word_list *start);

//modiefies word_list to insert next split
int	split_into_words(t_word_list *word)
{
	return (0);
}

// head = init_word_list(line);
// if (!head)
// 	return (NULL);
// head = expand(head);
// if (!head)
// 	return (NULL);

t_word_list	*expand(t_word_list *start)
{

}

// returns 0 if failed
int	subword_list(t_word_list *current, void (*split)(void *))
{
	t_word_list	*word_list;
	t_word_list	*tmp;
	int			i;

	word_list = split(current->word->word);
	if (!word_list || !word_list->word)
		return (0);
	i = strlen(word_list->word->word);
	while (current->word->word[i])
	{
		tmp = split(&current->word->word[i]);
		if (!tmp)
			return (0);
		word_list->next = tmp;
		word_list = tmp;
		i += strlen(word_list->word->word);
	}
	return (1);
}
