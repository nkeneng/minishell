/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/20 15:14:58 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_word_desc(void *word_desc)
{
	if (word_desc)
	{
		if (((t_word_desc *)word_desc)->word)
			free(((t_word_desc *)word_desc)->word);
		free(word_desc);
		word_desc = NULL;
	}
	return ;
}

void	*free_word_desc(t_word_desc **word_desc)
{
	if (word_desc && *word_desc)
		if ((*word_desc)->word)
			free((*word_desc)->word);
	free((*word_desc));
	(*word_desc) = NULL;
	return (NULL);
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
	ft_printf("word:	\"%s\"\n", desc->word);
	ft_printf("flags:	\n");
	return (1);
}

// makes a word and puts it inside word_desc from start of line to end and
// inherits flag to new item
t_word_desc	*wd_make_word(const char *line, const int end, const int flag)
{
	t_word_desc	*item;

	if (end <= 0)
		return (NULL);
	item = ft_calloc(sizeof(t_word_desc), 1);
	if (!item)
	{
		free(item);
		return (NULL);
	}
	item->word = ft_substr(line, 0, end);
	if (!item->word)
	{
		free_word_desc(&item);
		return (NULL);
	}
	item->flags = flag;
	return (item);
}

t_word_desc	*wd_fuse_words(t_word_desc *first, t_word_desc *second)
{
	t_word_desc	*new_word;
	char		*new_string;
	int			len1;
	int			len2;

	len1 = ft_strlen(first->word);
	len2 = ft_strlen(second->word);
	if (len1 == 0 && len2 == 0)
		return (second);
	new_string = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, first->word, len1 + 1);
	ft_strlcpy(new_string + len1, second->word, len2 + 1);
	new_word = wd_make_word(new_string, len1 + len2,
			first->flags | second->flags);
	free(new_string);
	free_word_desc(&second);
	return (new_word);
}
