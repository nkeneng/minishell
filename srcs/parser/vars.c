/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/22 10:35:14 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (word->word[i + 1])
	{
		if (!(ft_isalnum(word->word[i]) || word->word[i] == '_'))
			return ;
		i++;
	}
	if (word->word[i] == '=')
		word->flags += W_ASSIGNMENT;
	return ;
}
