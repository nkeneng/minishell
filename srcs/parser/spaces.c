/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:20:00 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 18:37:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

// takes a line started from character to check and returns number of characters
// that are whitespaces in a row (== index of last whitespace char)
int	ft_whitespace_seperator(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
		i++;
	return (i);
}

//returns 1 if it tried to perform memmove on string where every whitespace 
//constisting of one or several tabs, spaces or returns becomes a single space
//returns 0 if it couldn't do anything because item had quoted flags
//does not realloc!!
int	clean_whitespaces_to_space(t_word_desc *item)
{
	if (item->flags & W_SQUOTED || item->flags & W_DQUOTED)
		return (0);
	memmove_whitespaces_to_space(item->word);
	return (1);
}

// memmoves rest of line over more than one whitespaces
// but if single whitespace is not a space, it makes it a space
int	memmove_whitespaces_to_space(char *line)
{
	int	i;
	int	s;
	int	len;

	i = 0;
	s = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		s = ft_whitespace_seperator(&line[i]);
		if (s && !(s == 1 && line[i] == ' '))
		{
			line[i] = ' ';
			i++;
			s--;
			ft_memmove((void *) &line[i], (void *) &line[i + s], len - i + 1);
		}
		i++;
	}
	return (0);
}
