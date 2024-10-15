/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:19:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/15 17:21:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_word_list *expand(t_word_list *start);
t_command *concat_to_t_command(t_word_list *head, t_word_list *curr);

//modiefies word_list to insert next split
// int	split_into_words(t_word_list *word)
// {
// 	return (0);
// }

int	main()
{
	t_word_list	*item0;
	t_word_list	*item1;
	t_word_list	*item2;
	t_list		*lst;
	t_word_desc	*word_desc0;
	t_word_desc	*word_desc1;
	t_word_desc	*word_desc2;

	item2 = malloc(sizeof(t_word_list));
	item2->next = NULL;
	word_desc2 = malloc(sizeof(t_word_desc));
	item2->word = word_desc2;
	item2->word->flags = 0;
	item2->word->word = ft_strdup("last");
	item1 = malloc(sizeof(t_word_list));
	item1->next = item2;
	word_desc1 = malloc(sizeof(t_word_desc));
	item1->word = word_desc1;
	item1->word->flags = 0;
	item1->word->word = ft_strdup("|");
	item0 = malloc(sizeof(t_word_list));
	item0->next = item1;
	word_desc0 = malloc(sizeof(t_word_desc));
	item0->word = word_desc0;
	item0->word->flags = 0;
	item0->word->word = ft_strdup("first");
	lst = convert_to_command_lst(item1);
	ft_printf_lst(lst, ft_printf_command);
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

t_list	*convert_to_command_lst(t_word_list *head)
{
	t_word_list	*curr;
	t_list		*list_item;
	t_list		*list_head;
	t_list		*list_curr;
	t_command	*command;

	// head = init_word_list(line);
	// if (!head)
	// 	return (NULL);
	// head = expand(head);
	// if (!head)
	// 	return (NULL);
	curr = head;
	list_curr = NULL;
	list_head = list_curr;
	while (curr)
	{
		if ((head->word && head->word->word && head->word->word[0] == '|') || (head->word->flags >= C_PIPE && head->word->flags <= C_OPEN_OUT_APP))
		{
			command = concat_to_t_command(head, curr);
			list_item = ft_lstnew(command);
			if (!command || !list_item)
			{
				ft_lstclear(&list_item, ft_free_command);
				free_word_list(&head);
				return (NULL);
			}
			if (head->word->word[0] == '|')
				command->flags = C_PIPE;
			command->flags = curr->word->flags & PIPE_OR_REDIR_MASK;
			if (!list_curr)
				list_curr = list_item;
			else
			{
				list_curr->next = list_item;
				list_curr = list_curr->next;
			}
		}
		curr = curr->next;
	}
	return (list_head);
}

// concat from head up until current into one t_command
t_command *concat_to_t_command(t_word_list *head, t_word_list *curr)
{
	t_command	*command;
	t_word_list	*tmp;
	char		*command_str;

	command = malloc(sizeof(t_command));
	command_str = ft_calloc(1, 1);
	if (!command)
		return (NULL);
	command->flags = 0;
	command->cmd = command_str;
	tmp = head;
	while (tmp != curr)
	{
		if (tmp->word->flags == C_VAR)// and if Redirect (make a mask for that)
			return (NULL); //implement C_VAR handling and redirect handling here
		ft_strappend(command_str, tmp->word->word);
		free_word_desc(tmp->word);
		tmp = tmp->next;
		free(head);
		head = tmp;
	}
	free_word_desc(curr->word);
	free(curr);
	return (command);
}

// t_word_list	*expand(t_word_list *start)
// {
//
// }

// returns 0 if failed
// int	subword_list(t_word_list *current, void (*split)(void *))
// {
// 	t_word_list	*word_list;
// 	t_word_list	*tmp;
// 	int			i;
//
// 	word_list = split(current->word->word);
// 	if (!word_list || !word_list->word)
// 		return (0);
// 	i = strlen(word_list->word->word);
// 	while (current->word->word[i])
// 	{
// 		tmp = split(&current->word->word[i]);
// 		if (!tmp)
// 			return (0);
// 		word_list->next = tmp;
// 		word_list = tmp;
// 		i += strlen(word_list->word->word);
// 	}
// 	return (1);
// }
