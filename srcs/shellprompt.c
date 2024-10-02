/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/02 10:03:37 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

int	count_char_array(char **charray);
char	*rl_gets(void);
char	**parse_line(char *line);

int	main(int argc, char **argv, char **envp)
{
	char	**split_line;
	char	*line;
	int		num;
	int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = rl_gets();
		split_line = parse_line(line);
		num = count_char_array(split_line);
		exec_ret = start_pipex(num, split_line, envp);
		free_char_array(split_line, 0);
	}
	return (exec_ret);
}

char	**parse_line(char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	return (split_line);
}

char	*rl_gets(void)
{
	static char	*line;

	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("minishell$ ");
	if (!line || ft_strncmp("exit", line, 4) == 0)
		exit (0);
	ft_fprintf(1, "%s\n", line);
	if (line && *line) // seeing if line is not is unnecessary because auf previous check, leaving it in for later
		add_history(line);
	return (line);
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
