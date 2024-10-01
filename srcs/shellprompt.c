/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/01 18:23:22 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO: if readline returns NULL, exit minishell

int	count_char_array(char **charray);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	/* int		num; */
	/* char	**split_line; */

	(void)argc;
	(void)argv;
	(void)envp;
	line = readline("minishell$ ");
	ft_fprintf(1, "%s", line);
	/* split_line = ft_split(line, ' '); */
	/* num = count_char_array(split_line); */
	/* start_pipex(num, split_line, envp); */
	/* free_char_array(split_line, 0); */
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
