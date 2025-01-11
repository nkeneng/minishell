/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spaces_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:21:53 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/01 15:22:08 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_word_desc	*item;
	char		str[] = "   	this has		many      spaces";
	char		**array;

	item = malloc(sizeof(t_word_desc));
	item->word = ft_strdup(str);
	item->flags = 0;
	if (!clean_whitespaces_to_space(item))
		ft_printf("fail\n");
	ft_printf("%s\n", item->word);
	ft_printf("%i\n", item->flags);
	array = ft_split(item->word, ' ');
	ft_printf("the array from split:\n");
	ft_printf_char_array(array);
	free_word_desc(item);
	free_char_array(array, 0);
}
