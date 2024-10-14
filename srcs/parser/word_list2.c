/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:36:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/14 14:40:16 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*word_list_addback(t_word_list *word_list, t_word_desc *word)
{
	t_word_list	*new;
	t_word_list	*current;

	new = malloc(sizeof(t_word_list));
	if (!new)
		return (NULL);
	new->word = word;
	new->next = NULL;
	if (!word_list)
		return (new);
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

void	free_word_list(t_word_list **lst)
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
}

void	free_word_desc(t_word_desc *word_desc)
{
	if (word_desc)
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
