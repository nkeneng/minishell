/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:01:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/03 14:41:25 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//gets flag from beginning of word_desc->word and assigns flag to word
int	identify_word_type(t_word_desc *word)
{
	word->flags = sign_to_flag(word->word);
	return (word->flags);
}

//returns 1 after splitting around the item that should be an operator 
//or simmilar has right ammount of signs
//returns 3 if it is not the sign that converts to a flag
int	flag_correctly_delimeted(t_word_desc *item)
{
	int	flag;

	flag = sign_to_flag(item->word);
	if (flag)
	{
		if (flag & WM_DOUBLE_SIGN && item->word[2] == '\0')
			return (1);
		if (flag & WM_SINGLE_SING && item->word[1] == '\0')
			return (1);
		return (0);
	}
	return (3);
}

//only checks if sign is redirect or seperator
int	is_pipe_or_redirect(char *sign)
{
	if (*sign == '|')
	{
		if (*(sign + 1) == '|')
			return (W_OR);
		return (W_PIPE);
	}
	if (*sign == '&' && *(sign + 1) == '&')
		return (W_AND);
	if (*sign == '>')
	{
		if (*(sign + 1) == '>')
			return (W_OPEN_OUT_APP);
		return (W_OPEN_OUT_TRUNC);
	}
	if (*sign == '<')
	{
		if (*(sign + 1) == '<')
			return (W_HERE_DOC);
		return (W_OPEN_INFILE);
	}
	return (0);
}

int	is_quote(char *sign)
{
	if (*sign == '"')
		return (W_DQUOTED);
	if (*sign == '\'')
		return (W_SQUOTED);
	return (0);
}

// converts any sign into all possible flags
int	sign_to_flag(char *sign)
{
	int	i;

	i = is_quote(sign);
	if (i)
		return (i);
	if (*sign == '$')
		return (W_VAR);
	if (*sign == '=')
		return (W_ASSIGNMENT);
	return (is_pipe_or_redirect(sign));
}
