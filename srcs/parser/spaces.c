/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:20:00 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 10:56:55 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns 0 on failed allocation of string where every whitespace constisting
//of one or several tabs, spaces or returns becomes a single space
int	clean_whitespaces_to_space(t_word_desc *item)
{
	int		i;
	char	new_string;

	if (item->flags & W_SQUOTED || item->flags & W_DQUOTED)
		return (2);
	i = 0;
	while (item->word[i] && item)
	{}
	return (0);
}

char	*whitespaces_to_single_space(char *line)
{
	char	*clean_line;
	int		i;
	int		c;
	int		len;

	c = 1;
	i = 0;
	len = ft_strlen(line);
	clean_line = malloc((len + 1) * sizeof(char));
	i = ft_whitespace_seperator(line);
	if (i)
		clean_line[0] = ' ';
	else
		clean_line[0] = *line;
	while (*line)
	{
		line++;
		clean_line[c] = line[i];
		i = ft_whitespace_seperator(line);
	}
	

}
