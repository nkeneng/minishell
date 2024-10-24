/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:53:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 15:33:01 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// give this " or ' as sign to return 1 if even ammount or 0 if none, or -1 err
int	missing_close_sign(char *line, char sign)
{
	int	ammount;

	ammount = 0;
	while (*line)
	{
		line = ft_strchr(line, sign);
		if (!line)
			break ;
		ammount++;
		line++;
	}
	if (ammount == 0)
		return (0);
	else if (!(ammount % 2))
		return (1);
	else
		return (-1);
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
