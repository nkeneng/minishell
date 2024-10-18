/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/18 13:51:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks if line is valid var name and sets flag if it is. rewrite this to only check var=
//write different check for assignment
void	ft_is_var_name(t_word_desc *word)
{
	int	i;
	int	equals;

	equals = 0;
	if (word->flags & (W_SQUOTED | W_DQUOTED))
		return ;
	if (!(ft_isalpha(word->word[0] || word->word[0] == '_')))
		return ;
	i = 1;
	while (word->word[i])
	{
		if (word->word[i] == '=' && !(word->word[i] == '\0'))
		{
			i++;
			equals = 1;
		}
		else if (!(ft_isalnum(word->word[i]) || word->word[i] == '_'))
			return ;
		else
			i++;
	}
	if (equals)
		word->flags += W_VAR;
}
