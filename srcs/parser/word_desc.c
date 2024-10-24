/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 12:02:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_word_desc(t_word_desc *word_desc)
{
	if (word_desc)
		if (word_desc->word)
			free(word_desc->word);
	free(word_desc);
	return ;
}

// makes a word and puts it inside word_desc from start of line to end and applies flag
t_word_desc	*make_word(const char *line, const int end, const int flag)
{
	t_word_desc	*item;

	item = ft_calloc(sizeof(t_word_desc), 1);
	if (!item)
	{
		free(item);
		return (NULL);
	}
	item->word = ft_substr(line, 0, end);
	if (!item->word)
	{
		free_word_desc(item);
		return (NULL);
	}
	item->flags = flag;
	return (item);
}
