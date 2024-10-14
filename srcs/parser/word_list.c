/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:36:49 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/14 09:49:01 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	char	*input;
	char	hardstring[] = "Hello | mynopspace|pipe";
	t_word_list	**word_list;

	input = ft_substr(hardstring, 0, ft_strlen(hardstring));
	word_list = make_word_list( input);
	ft_printf_word_list(*word_list);
}

t_word_list **make_word_list(char *line)
{
	t_word_list	**word_list_head;
	t_word_list	*word_list;
	t_word_list	*tmp;
	int			i;

	word_list_head = malloc(sizeof(t_word_list));
	word_list_head = &word_list;
	word_list = get_next_word(line);
	if (!word_list || ! word_list->word )
		return (NULL);
	ft_printf("current word:%s\n",word_list->word->word);
	i = strlen(word_list->word->word);
	ft_printf("i:%d\n", i);
	while (line[i] && i < 10)
	{
		tmp = get_next_word(&line[i]);
		ft_printf("tmp word:%s\n",tmp->word->word);
		if (!tmp)
			return (NULL);
		// if (word_list->word->word[0] == '|')
		// {
		// 	i += strlen(word_list->word->word);
		// 	tmp->word->flags = C_PIPE;
		// 	free_word_desc(word_list->word);
		// 	word_list->word = tmp->word;
		// 	ft_printf("word_list:%s\n",word_list->word->word);
		// }
		// else
		// {
		word_list->next = tmp;
		word_list = word_list->next;
		// }
		ft_printf("current new word:%s\n",word_list->word->word);
		i += strlen(word_list->word->word);
		ft_printf("i:%d\n", i);
	}
	return (word_list_head);
}

t_word_list	*word_list_addback(t_word_list word_list_head, t_word_desc *word)
{
	t_word_list	*new;
	t_word_list	*current;
	new = malloc(sizeof(t_word_list));
	if (!new)
		return (NULL);
	new->word = word;
	new->next = NULL;
	if (!word_list_head)
		return (new);
	current = word_list_head;
	while (current->next)
		current = current->next;
	current->next = new;
	return (new);
	}
}

void	ft_printf_word_list(t_word_list *word_list)
{
	while (word_list)
	{
		ft_printf("1: %s\n", word_list->word->word);
		ft_printf("1 flag: %d\n", word_list->word->flags);
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

t_word_list *get_next_word(char *line)
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
			return(NULL);
	word = ft_calloc(sizeof(t_word_list), 1);
	word->word = create_word(substr, flag);
	if (!word->word)
	{
		free(word);
		return (NULL);
	}
	return (word);
}

t_word_desc *create_word(char *word, int flags)
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
