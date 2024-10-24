/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:01:31 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 12:48:22 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//gets flag from sign and assigns flag to word
int	identify_word_type(t_word_desc *word)
{
	int	i;
	int	flag;

	i = 0;
	if (word->word[i] == '|')
		flag = (W_PIPE);
	else if (word->word[i] == '>')
	{
		if (word->word[i + 1] == '>')
			flag = (W_OPEN_OUT_APP);
		flag = (W_OPEN_OUT_TRUNC);
	}
	else if (word->word[i] == '<')
		flag = (W_OPEN_INFILE);
	else
		return (0);
	word->flags = flag;
	return (flag);
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

int	sign_to_flag(char *sign)
{
	if (*sign == '"')
		return (W_DQUOTED);
	if (*sign == '\'')
		return (W_SQUOTED);
	if (*sign == '$')
		return (W_VAR);
	if (*sign == '=')
		return (W_ASSIGNMENT);
	return (is_pipe_or_redirect(sign));
}
