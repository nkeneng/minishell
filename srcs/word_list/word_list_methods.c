/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:36:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/12 14:30:50 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list	*wl_init(char *line)
{
	t_word_list	*first_item;
	t_word_desc	*desc;

	desc = wd_make_word(line, ft_strlen(line), 0);
	if (!desc)
		return (NULL);
	first_item = wl_addback(NULL, desc);
	return (first_item);
}

t_word_list	*wl_addback(t_word_list *word_list, t_word_desc *word)
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
	new->prev = NULL;
	if (!word_list)
	{
		word_list = new;
		return (new);
	}
	current = word_list;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (new);
}

//inserts word after t_word_list item called item
t_word_list	*wl_insert(t_word_list *item, t_word_desc *word)
{
	t_word_list	*new;

	if (!word)
		return (NULL);
	new = malloc(sizeof(t_word_list));
	if (!new)
		return (NULL);
	new->word = word;
	if (!item)
	{
		new->next = NULL;
		return (new);
	}
	new->next = item->next;
	item->next->prev = new;
	item->next = new;
	new->prev = item;
	return (new);
}

void	ft_printf_word_list(t_word_list *word_list)
{
	int	i;

	i = 1;
	(void)i;
	while (word_list)
	{
		ft_printf_word_desc(word_list->word);
		ft_printf("\n");
		i++;
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
			current = NULL;
			(current) = next;
		}
	}
	return (NULL);
}
