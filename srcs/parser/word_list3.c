/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:19:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 10:06:52 by lmeubrin         ###   ########.fr       */
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

// int	main()
// {
// 	t_word_list	*word_list_head;
// 	t_list		*lst;
// 	// int		exec_ret;
//
// 		word_list_head = make_word_list("here we have a|test |last");
// 		ft_printf_word_list(word_list_head);
// 		lst = convert_to_command_lst(word_list_head);
// 		ft_printf_lst(lst, ft_printf_command);
// 		free_word_list(&word_list_head);
// 	return (0);
// }

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
	t_word_list	*tmp;
	t_list		*list_item;
	t_list		*list_head;
	t_list		*list_curr;
	t_command	*command;
	int			flag;

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
		if ((curr->word && curr->word->word && curr->word->word[0] == '|') || (curr->word->flags >= C_PIPE && curr->word->flags <= C_OPEN_OUT_APP))
		{
			if (curr->word->word[0] == '|')
				flag = C_PIPE;
			flag &= curr->word->flags & PIPE_OR_REDIR_MASK;
			command = concat_to_t_command(head, curr);
			list_item = ft_lstnew(command);
			if (!command || !list_item)
			{
				ft_lstclear(&list_item, ft_free_command);
				free_word_list(&head);
				return (NULL);
			}
			if (!list_curr)
				list_curr = list_item;
			else
			{
				list_curr->next = list_item;
				list_curr = list_curr->next;
			}
			head = curr->next;
		}
		tmp = curr->next;
		free_word_desc(curr->word);
		free(curr);
		curr = tmp;
	}
	return (list_head);
}

// concat from head up until current into one t_command
t_command *concat_to_t_command(t_word_list *head, t_word_list *curr)
{
	t_command	*command;
	t_word_list	*tmp;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->flags = 0;
	command->cmd = ft_strdup(head->word->word);
	if (!command->cmd)
		free(command);
	tmp = head->next;
	if (head == curr)
	{
		free_word_desc(head->word);
		free(head);
	}
	while (tmp != curr && head != curr)
	{
		if (tmp->word->flags == C_VAR)// and if Redirect (make a mask for that)
			return (NULL); //implement C_VAR handling and redirect handling here
		ft_strappend(command->cmd, tmp->word->word);
		head = tmp;
		tmp = tmp->next;
		free_word_desc(head->word);
		free(head);
	}
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
