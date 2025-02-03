/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:51:34 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 10:52:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// does a strjoin but frees s1
char	*ft_freejoin(char *s1, char *s2)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	free(s1);
	return (joined_str);
}

int	free_char_array(char **array, int ret)
{
	int	i;

	i = -1;
	if (!array)
		return (ret);
	while (array[++i])
		free(array[i]);
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

int	ft_env_size(t_env *envp)
{
	int	i;

	i = 0;
	while (envp[i].key)
		i++;
	return (i);
}
