/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/14 18:35:57 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list *expand(t_word_list *start)

//modiefies word_list to insert next split
int	split_into_words(t_word_list *word)
{
	return (0);
}

t_word_list	*init_word_list(char *line)
{
	t_word_list	*first_item;
	t_word_desc	*desc;

	desc = create_word(line, 0);
	if (!desc)
		return (NULL);
	first_item = word_list_addback(NULL, desc);
	return (first_item);
}

t_list	*convert_to_command_lst(char *line)
{
	t_word_list	*head;
	t_word_list	*curr;
	t_list		*command_list;
	t_command	*command;
	int			flag;

	head = init_word_list(line);
	if (!head)
		return (NULL);
	head = expand(head);
	if (!head)
		return (NULL);
	while (curr)
	{
		if (curr->word->flags >= C_PIPE && curr->word->flags <= C_OPEN_OUT_APP)
		{
			command = concat_to_t_command(head, curr); // concat from head up until current into one command
			if (!command)
			{
				ft_lstclear(&command_list, ft_free_command);
				free_word_list(&head);
			}
			command->flag = curr->word->flags & PIPE_OR_REDIR_MASK;
		}
		curr = curr->next;
	}
}

t_word_list	*expand(t_word_list *start)
{

}

// returns 0 if failed
int	subword_list(t_word_list *current, void (*split)(void *))
{
	t_word_list	*word_list;
	t_word_list	*tmp;
	int			i;

	word_list = split(current->word->word);
	if (!word_list || !word_list->word)
		return (0);
	i = strlen(word_list->word->word);
	while (current->word->word[i])
	{
		tmp = split(&current->word->word[i]);
		if (!tmp)
			return (0);
		word_list->next = tmp;
		word_list = tmp;
		i += strlen(word_list->word->word);
	}
	return (1);
}

t_word_list	*make_word_list(char *line)
{
	t_word_list	*word_list_head;
	t_word_list	*word_list;
	t_word_list	*tmp;
	int			i;

	word_list = split_at_pipes(line);
	if (!word_list || !word_list->word)
		return (NULL);
	word_list_head = word_list;
	i = strlen(word_list->word->word);
	while (line[i])
	{
		tmp = split_at_pipes(&line[i]);
		if (!tmp)
			return (NULL);
		word_list->next = tmp;
		word_list = tmp;
		i += strlen(word_list->word->word);
	}
	return (word_list_head);
}

t_word_list	*split_at_pipes(char *line)
{
	int			i;
	char		*substr;
	t_word_list	*word;
	int			flag;

	if (!line)
		return (NULL);
	flag = 0;
	i = 0;
	if (line[i] == '|')
		while (line[i] == '|')
			i++;
	else
		while (line[i] && '|' != line[i])
			i++;
	substr = ft_substr(line, 0, i);
	if (!substr)
		return (NULL);
	word = ft_calloc(sizeof(t_word_list), 1);
	if (!word)
		return (NULL);
	word->word = create_word(substr, flag);
	if (!word->word)
		return (NULL);
	return (word);
}
