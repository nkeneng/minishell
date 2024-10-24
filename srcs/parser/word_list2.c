/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:36:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 12:03:15 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*init_word_list(char *line)
{
	t_word_list	*first_item;
	t_word_desc	*desc;

	desc = make_word(line, ft_strlen(line), 0);
	if (!desc)
		return (NULL);
	first_item = word_list_addback(NULL, desc);
	return (first_item);
}

t_word_list	*word_list_addback(t_word_list *word_list, t_word_desc *word)
{
	t_word_list	*new;
	t_word_list	*current;

	if (!word)
		return (NULL);
	new = malloc(sizeof(t_word_list));
	if (!new)
		return (NULL);
	new->word = word;
	new->next = NULL;
	if (!word_list)
	{
		word_list = new;
		return (new);
	}
	current = word_list;
	while (current->next)
		current = current->next;
	current->next = new;
	return (new);
}

t_word_list	*word_list_insert(t_word_list *word_list, t_word_desc *word)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (!new)
		return (NULL);
	new->word = word;
	if (!word_list)
	{
		new->next = NULL;
		return (new);
	}
	new->next = word_list->next;
	word_list->next = new;
	return (new);
}

void	ft_printf_word_list(t_word_list *word_list)
{
	int	i;

	i = 1;
	while (word_list)
	{
		ft_printf("%d: %s\n", i, word_list->word->word);
		ft_printf("%d flag: %d\n", i++, word_list->word->flags);
		word_list = word_list->next;
	}
}

void	*free_word_list(t_word_list **lst)
{
	t_word_list	*current;
	t_word_list	*next;

	if (lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			if (current->word && current->word->word)
				free_word_desc(current->word);
			free(current);
			(current) = next;
		}
	}
	return (NULL);
}
