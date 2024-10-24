/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_to_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:19:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 15:26:59 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*convert_to_command_lst(t_word_list *head)
{
	t_word_list	*curr;
	t_list		*list_head;
	t_list		*list_curr;
	t_command	*command;
	int			flag;

	curr = head;
	list_curr = NULL;
	list_head = NULL;
	while (curr)
	{
		flag = identify_word_type(curr->word);
		if (!flag || curr->next == NULL)
		{
			flag &= curr->word->flags & PIPE_OR_REDIR_MASK;
			command = concat_to_t_command(head, curr);
			list_curr = ft_lstcreateaddback(&list_curr, (void *) command);
			if (!command || !list_curr)
			{
				ft_lstclear(&list_head, ft_free_command);
				free_word_list(&head);
				return (NULL);
			}
			head = curr->next;
		}
		if (list_head == NULL)
			list_head = list_curr;
		curr = curr->next;
	}
	return (list_head);
}

// heads up, this was majorly changed, idk if working...
// concat from head up until current into one t_command
t_command	*concat_to_t_command(t_word_list *head, t_word_list *curr)
{
	t_command	*command;
	char		*concat_str;
	t_word_list	*tmp;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->flags = curr->word->flags;
	concat_str = ft_strdup(head->word->word);
	if (!concat_str)
		return (NULL);
	tmp = head->next;
	while (tmp != curr && head != curr)
	{
		if (tmp->word->flags == C_VAR)// and if Redirect (make a mask for that)
			return (NULL); //implement C_VAR handling and redirect handling here
		ft_strappend(concat_str, tmp->word->word);
		if (!concat_str)
			return (NULL);
		head = tmp;
		tmp = tmp->next;
		free_word_desc(head->word);
		free(head);
	}
	command->cmd = ft_split(concat_str, ' ');
	if (!command->cmd)
		free(command);
	return (command);
}
