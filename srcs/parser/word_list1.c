/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_list1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:43:51 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 14:16:09 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_list_head;
	t_list		*lst;
	char	*line;
	// int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = rl_gets();
		while (missing_close_sign(line, '\''))
			ft_strappend(line, rl_gets());
		word_list_head = make_word_list(line);
		ft_printf_word_list(word_list_head);
		lst = convert_to_command_lst(word_list_head);
		ft_printf_lst(lst, ft_printf_command);
		free_word_list(&word_list_head);
		// exec_ret = do_list(&wordlist, envp);
	}
	return (0);
	// return (exec_ret);
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
