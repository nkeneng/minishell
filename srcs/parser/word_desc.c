/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/22 15:37:50 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	identify_word_type(t_word_desc *word)
{
	int	i;
	int	flag;

	i = 0;
	if (word->word[i] == '|')
		flag = (W_PIPE);
	else if (word->word[i] == '>')
	{
		if (word->word[i + 1] == '>')
			flag = (W_OPEN_OUT_APP);
		flag = (W_OPEN_OUT_TRUNC);
	}
	else if (word->word[i] == '<')
		flag = (W_OPEN_INFILE);
	else
		return (0);
	word->flags = flag;
	return (flag);
}

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
