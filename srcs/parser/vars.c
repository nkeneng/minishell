/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 15:56:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*split_for_var(char *line);

//checks if line is valid var name and sets flag if it is.
//write different check for word after assignment
void	ft_is_var_name(t_word_desc *word)
{
	int	i;

	if (word->flags & (W_SQUOTED | W_DQUOTED))
		return ;
	if (!(ft_isalpha(word->word[0] || word->word[0] == '_')))
		return ;
	i = 1;
	while (word->word[i])
	{
		if (!(ft_isalnum(word->word[i]) || word->word[i] == '_'))
			return ;
		i++;
	}
	if (word->word[i] == '=')
		word->flags += W_ASSIGNMENT;
	return ;
}

//no need for this, just implement ft_is_var_name
t_word_list	*split_for_var(char *line)
{
	t_word_list	*head;
	int			i;
	int			start;

	i = 1;
	head = NULL;
	while (line[i] && line[i] != '=')
		i++;
	start = i;
	while (start >= 0 && line[start] != ' ')
		start--;
	while (line[i] && line[i] != ' ')
		i++;
	if (start)
	{
		word_list_addback(head, make_word(line, start, 0));
		if (!head)
			return (NULL);
	}
	word_list_addback(head, make_word(&line[start], i, W_VAR));
	return (head);
}
