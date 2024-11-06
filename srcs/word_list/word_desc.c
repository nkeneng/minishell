/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/06 13:58:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_word_desc(t_word_desc *word_desc)
{
	if (word_desc)
		if (word_desc->word)
			free(word_desc->word);
	free(word_desc);
	word_desc = NULL;
	return ;
}

int	ft_printf_word_desc(void *word_desc)
{
	t_word_desc	*desc;

	if (!word_desc)
	{
		ft_printf("(null word_desc)\n");
		return (0);
	}
	desc = (t_word_desc *)word_desc;
	ft_printf("word_desc at %p:\n", (void *)desc);
	if (!desc->word)
	{
		ft_printf("(null word)\n");
		return (0);
	}
	if ((void *)desc->word < (void *)0x1000)
	{
		ft_printf("(invalid word pointer)\n");
		return (0);
	}
	ft_printf("word:	%s\n", desc->word);
	ft_printf("flags:	%d\n", desc->flags);
	return (1);
}

// makes a word and puts it inside word_desc from start of line to end and
// inherits flag to new item
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
