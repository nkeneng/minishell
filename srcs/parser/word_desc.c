/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:19:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/17 16:22:24 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	identify_word_type(t_word_desc *word)
{
	int	i;
	int	flag;

	i = 0;
	if (word->word[i] == '|')
		flag = (C_PIPE);
	else if (word->word[i] == '>')
	{
		if (word->word[i + 1] == '>')
			flag = (C_OPEN_OUT_APP);
		flag = (C_OPEN_OUT_TRUNC);
	}
	else if (word->word[i] == '<')
		flag = (C_OPEN_INFILE);
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

t_word_desc	*create_word(char *word, int flags)
{
	t_word_desc	*element;

	element = malloc(sizeof(t_word_desc));
	if (element == NULL)
	{
		free(element);
		return (NULL);
	}
	element->word = word;
	element->flags = flags;
	return (element);
}
