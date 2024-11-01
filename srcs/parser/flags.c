/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:01:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 17:06:11 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//gets flag from beginning of word_desc->word and assigns flag to word
int	identify_word_type(t_word_desc *word)
{
	int	flag;

	flag = sign_to_flag(word->word);
	word->flags = flag;
	return (flag);
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
		return (W_OPEN_INFILE);
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
