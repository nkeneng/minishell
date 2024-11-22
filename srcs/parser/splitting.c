/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:57:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/22 09:46:37 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Breaks the input into words and operators, obeying the quoting rules 
//described in Quoting. These tokens are separated by metacharacters. 
//Alias expansion is performed by this step (see Aliases).

// use this to create new element containting one or multiple consecutive
// '&' or '|' or << or >> or < or >
t_word_list	*split_around(t_word_desc *input)
{
	int			i;
	int			pi;
	t_word_list	*h;
	t_word_list	*tmp;

	h = NULL;
	i = 0;
	pi = 0;
	while (input->word[i])
	{
		i += (next_word_till_metachar(&input->word[i]));
		tmp = wl_addback(h, wd_make_word(&input->word[pi], i - pi, 0));
		if (!h)
			h = tmp;
		if (!tmp)
		{
			free_word_list(&h);
			return (NULL);
		}
		pi = i;
	}
	return (h);
}

int	next_word_till_metachar(char *line)
{
	int		i;
	char	sign;

	i = 0;
	sign = *line;
	if (is_quote(line))
	{
		i++;
		while (line[i] != sign)
			i++;
		if (line[i++])
			return (i++);
	}
	else if (sign == '$')
		i += ft_is_var_till(&line[i + 1]) + 1;
	else if (sign_to_flag(line))
		while (line[i] == sign)
			i++;
	else
		while (line[i] && !sign_to_flag(&line[i]))
			i++;
	i += ft_whitespace_seperator(&line[i]); // uncomment this to add the whitespace at the end of every sign, breaks checking for right operators dleimited by \0
	return (i);
}

//returns iterator after continuing over sign or until next letter would be sign
int	next_word_till(char *line, char sign)
{
	int	i;

	i = 0;
	if (line[i] == sign)
		while (line[i] == sign)
			i++;
	else
		while (line[i] && sign != line[i])
			i++;
	return (i);
}
