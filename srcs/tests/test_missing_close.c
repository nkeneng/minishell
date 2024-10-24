/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_missing_close.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:32:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 15:32:30 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//main to test missing_close functions
int	main(int argc, char **argv)
{
	(void)argc;
	ft_printf("string:\n%s\n", argv[1]);
	ft_printf("contains closing brackets: %d\n", missing_close_bracket(argv[1]));
	ft_printf("contains closing single quote: %d\n", missing_close_sign(argv[1], '\''));
	ft_printf("contains closing double quote: %d\n", missing_close_sign(argv[1], '"'));
}
