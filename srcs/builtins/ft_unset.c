/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:48:49 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/05 12:55:06 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char **args, t_env **envp)
{
	int	i;
	int	j;

	if (args)
	{
		if (count_char_array(args) == 1)
		{
			ft_printf("export: not enough arguments\n");
			free_char_array(args, 0);
			return ;
		}
		i = 1;
		while (args[i])
		{
			j = 0;
			while ((*envp)[j].key)
			{
				if (ft_strncmp((*envp)[j].key, args[i], ft_strlen(args[i])) == 0)
				{
					free((*envp)[j].key);
					free((*envp)[j].value);
					while ((*envp)[j].key)
					{
						(*envp)[j] = (*envp)[j + 1];
						j++;
					}
					break ;
				}
				j++;
			}
			i++;
		}
	}
}
