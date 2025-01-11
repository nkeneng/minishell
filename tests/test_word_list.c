/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:54:18 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/25 11:10:23 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*lst;

	(void)argc;
	(void)argv;
	// while (1)
	// {
		// line = rl_gets();
		line = "ls -l | cat -e";
		lst = parse_input(line, envp);
	// }
	ft_lstclear(&lst, ft_free_command);
	return (0);
}
