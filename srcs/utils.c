/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:51:34 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/07 08:27:15 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_char_array(char **array, int ret)
{
	int	i;

	i = 0;
	if (!array)
		return (ret);
	while (array[i])
		free(array[i++]);
	free(array);
	return (ret);
}

int	rperror(char *str)
{
	perror(str);
	return (errno);
}

// returns number of items in array of strings
int	count_char_array(char **charray)
{
	int	i;

	i = 0;
	while (charray[i] != NULL)
		i++;
	return (i);
}
