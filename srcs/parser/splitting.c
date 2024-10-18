/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:57:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/18 13:04:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* t_word_desc	*create_word(char *word, int flags); */
/* t_word_list	*get_next_word(char *line); */
/* t_word_list	*make_word_list(char *line); */


// use this to split after ' ' or '=' or '|' or << or >> or < or >
t_word_list	*split_after(t_word_desc *input, char sign)
{
	int			i;
	int			previ;
	t_word_list	*head;
	t_word_list	*tmp;
	int			flag;

	head = NULL;
	flag = get_flag_from_sign(sign);
	i = 0;
	previ = 0;
	while (input->word[i])
	{
		if (input->word[i] == sign)
			while (input->word[i] == sign)
				i++;
		else
			while (input->word[i] && sign != input->word[i])
				i++;
		tmp = word_list_addback(head, make_word(&input->word[previ], i - previ, flag));
		if (!head)
			head = tmp;
		if (!tmp)
		{
			free_word_list(&head);
			return (NULL);
		}
		previ = i;
	}
	return (head);
}

int	get_flag_from_sign(char sign)
{
	if (sign == '\'')
		return (W_SQUOTED);
	if (sign == '"')
		return (W_DQUOTED);
	if (sign == '|')
		return (W_EXECUTE);
	if (sign == '$')
		return (W_HASDOLLAR);
	if (sign == '&')
		return (W_AND);
	if (sign == '=')
		return (W_VAR);
	return (0);
}
/**/
/* //Breaks the input into words and operators, obeying the quoting rules  */
/* //described in Quoting. These tokens are separated by metacharacters.  */
/* //Alias expansion is performed by this step (see Aliases). */
/* t_word_list	*split_into_words(char *line) */
/* { */
/* 	t_word_list	*word_list; */
/* 	t_word_list	*current_word; */
/* 	char		*word; */
/* 	char		last_special; */
/* 	char		*next_special; */
/* 	int			i; */
/* 	int			start_split; */
/**/
/* 	word_list = current_word; */
/* 	current_word = NULL; */
/* 	start_split = 0; */
/* 	while (line[i]) */
/* 	{ */
/* 		next_special = ft_strchr("\"\'$()<>|", line[i]); */
/* 		if (next_special) */
/* 		{ */
/* 			if (start_split == i) */
/* 			{ */
/* 				last_special = *next_special; */
/* 				continue ; */
/* 			} */
/* 			if (*next) */
/* 			{} */
/* 			if (last_special == '\'' && last_special == *next_special) */
/* 			{} */
/* 			if (*next_special == '\'') */
/* 			{} */
/* 		} */
/**/
/* 		i++; */
/* 	} */
/* 	return (word_list); */
/* } */
/**/
/* // produces t_word_list element from start of line to sign */
/* t_word_list	*seperate_at(char *line, char sign) */
/* { */
/* 	int			i; */
/* 	t_word_desc	*element; */
/**/
/* 	i = 0; */
/* 	while (line[i]) */
/* 	{ */
/* 		if (line[i] == sign) */
/* 		{ */
/* 				element->word = ft_substr(line, 0, i - 1); */
/* 				if (element->word == NULL) */
/* 					return (NULL); */
/* 				if (sign == '|') */
/* 					element->flags = C_PIPE; */
/* 				else if (sign == '<') */
/* 					element->flags = C_OPEN_INFILE; */
/* 				else if (sign == '>') */
/* 					element->flags = C_OPEN_OUT_TRUNC; */
/* 				else if (sign == '>') */
/* 					element->flags = C_OPEN_OUT_APP; */
/* 		} */
/* 		i++; */
/* 	} */
/* } */
/**/
/* int	main(int argc, char **argv, char **envp) */
/* { */
/* 	t_list	*args; */
/* 	char	*line; */
/* 	int		exec_ret; */
/**/
/* 	(void)argc; */
/* 	(void)argv; */
/* 	(void)envp; */
/* 	while (1) */
/* 	{ */
/* 		line = rl_gets(); */
/* 		while (missing_close_sign(line, '\'')) */
/* 			ft_strappend(line, rl_gets()); */
/* 		args = parse_input(line, envp); */
/* 		num = ft_lstsize(args); */
/* 		exec_ret = do_list(&args, envp); */
/* 	} */
/* 	ft_lstclear(&args, 0); */
/* 	return (exec_ret); */
/* } */
