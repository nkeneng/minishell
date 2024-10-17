/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:14 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/17 15:49:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//checks if line is valid var name and sets flag if it is.
void	ft_is_var_name(t_word_desc *word)
{
	int	i;

	i = 0;
	if (word->flags & (W_SQUOTED | W_DQUOTED))
		return ;
	while (word->word[i])
	{
		if (!(ft_isalnum(word->word[i]) || word->word[i] == '_'))
			return ;
	}
	word->flags += W_VAR;
}
