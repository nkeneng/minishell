/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strexchange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:50:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/24 10:21:36 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//function to exchange the string to_replace and its preceeding $ with new_string
// in the original string and frees the original
// returns a malloced string or NULL if allocation failed
char	*ft_strexchange(char *original, char *old, int len_old, char *new_str)
{
	char	*result;
	char	*start;

	result = malloc(ft_strlen(original) - len_old + ft_strlen(new_str) + 1);
	if (!result)
		return (NULL);
	start = result;
	while (*original != '$')
		*(result++) = *(original++);
	original++;
	original += len_old;
	while (*new_str)
		*(result++) = *(new_str++);
	while (*original)
		*(result++) = *(original++);
	*result = '\0';
	return (start);
}
