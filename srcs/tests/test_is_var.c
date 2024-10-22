/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:47:36 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/18 13:47:48 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv)
{
	t_word_desc	*word;

	(void)argc;
	word = ft_calloc(sizeof(t_word_desc), 1);
	word->word = ft_strdup(argv[1]);
	word->flags = 0;
	ft_is_var_name(word);
	ft_printf("string:\n%s\n", argv[1]);
	if (word->flags & W_VAR)
		ft_printf("is var\n");
	else
		ft_printf("is not var\n");
	free_word_desc(word);
}
