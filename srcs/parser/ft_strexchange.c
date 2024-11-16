/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strexchange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:50:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 17:51:03 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//function to exchange the string to_replace a. its preceeding $ with new_string
// in the original string and frees the original
// returns a malloced string or NULL if allocation failed
char	*ft_strexchange(char *original, char *to_replace, char *new_str)
{
	int		ltoreplace;
	char	*result;
	char	*start;

	ltoreplace = ft_strlen(to_replace);
	result = malloc(ft_strlen(original) - ltoreplace + ft_strlen(new_str) + 1);
	if (!result)
		return (NULL);
	start = result;
	while (*original != '$')
		*(result++) = *(original++);
	original++;
	original += ltoreplace;
	while (*new_str)
		*(result++) = *(new_str++);
	while (*original)
		*(result++) = *(original++);
	*result = '\0';
	return (start);
}
