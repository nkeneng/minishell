/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:53:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/09 12:22:16 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// give this " or ' as sign to return if even ammount
int	missing_close_sign(char *line, char sign)
{
	int	 ammount;

	ammount = 0;
	while (*line)
	{
		line = ft_strchr(line, sign);
		if (!line)
			break ;
		ammount++;
		line++;
	}
	if (!(ammount % 2) || ammount == 0)
		return (0);
	else
		return (1);
}

// returns 0 if all good, positive number if missing closing bracket,
// negative if missing opening bracket
int	missing_close_bracket(char *line)
{
	int	open;

	open = 0;
	while (*line)
	{
		if (*line == '(')
			open++;
		if (*line == ')')
			open--;
		if (open < 0)
			return (-1);
		line++;
	}
	return (open);
}

//main to test missing_close functions
/* int	main(int argc, char **argv) */
/* { */
/* 	(void)argc; */
/* 	ft_printf("string:\n%s\n", argv[1]); */
/* 	ft_printf("contains closing brackets: %d\n", missing_close_bracket(argv[1])); */
/* 	ft_printf("contains closing single quote: %d\n", missing_close_sign(argv[1], '\'')); */
/* 	ft_printf("contains closing double quote: %d\n", missing_close_sign(argv[1], '"')); */
/* } */
