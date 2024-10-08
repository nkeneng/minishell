/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:18:07 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/05 13:18:37 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void ft_export(char **args)
{
	int i;
	int ret;
	char *key;
	char *value;
	i = 1;
	while (args[i])
	{
		ret = ft_split_env(args[i], &key, &value);
		if (ret == -1)
			return ;
		if (ret == 0)
			ft_setenv(key, value);
		free(key);
		free(value);
		i++;
	}
}
