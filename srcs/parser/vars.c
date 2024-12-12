/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/11 11:42:09 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// checks if there are any ~ or $ with valid variable names 
// if there are ~ or to be expanded $: unsets W_EXPANDED flag, returns 1
// returns 0 if there are no ~ or $ with valid var names
int	contains_more_vars(t_word_desc *item)
{
	char	*var_start;

	if (item->flags & (W_SQUOTED))
		return (0);
	if (ft_strchr(item->word, '~'))
	{
		item->flags &= ~W_EXPANDED;
		return (1);
	}
	var_start = ft_strchr(item->word, '$');
	while (var_start && *var_start && *(var_start + 1))
	{
		if (ft_is_var_till(var_start + 1) || *(var_start + 1) == '?')
		{
			item->flags &= ~W_EXPANDED;
			return (1);
		}
		var_start = ft_strchr(var_start + 1, '$');
	}
	return (0);
}

//checks if line is valid var name and sets flag if it is.
//write different check for word after assignment
void	ft_is_var_name(t_word_desc *word)
{
	int	i;

	if (word->flags & (W_SQUOTED | W_DQUOTED))
		return ;
	if (!(ft_isalpha(word->word[0] || word->word[0] == '_')))
		return ;
	i = 1;
	while (word->word[i])
	{
		if (!(ft_isalnum(word->word[i]) || word->word[i] == '_'))
			return ;
		i++;
	}
	if (word->word[i] == '=')
		word->flags += W_ASSIGNMENT;
	return ;
}

// function that checks if sign is a special character in bash
// speacial chars: ? $ @ ! - #
// returns 1 if true, 0 if false
int	ft_is_special(char c)
{
	if (c == '?' || c == '$' || c == '@' || c == '!' || c == '-' || c == '#' \
	|| c == '.' || c == '+' || c == '-' || c == '/' || c == '*')
		return (1);
	return (0);
}

// function that checks if the word is a valid variable name
// return 0 if it is not and should not be treated as varname,
// return iterator of first sign that is not part of varname anymore
// takes a line after $ sign
int	ft_is_var_till(char *line)
{
	int	i;

	if (!(ft_isalpha(line[0]) || line[0] == '_'))
		return (0);
	i = 1;
	while (line[i])
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
			return (i);
		i++;
	}
	// while (line[i] && line[i] != '=')
	// {
	// 	if (!(ft_isalnum(line[i]) || line[i] == '_'))
	// 		return (0);
	// 	i++;
	// }
	return (i);
}
