/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/08 19:44:43 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_char_array(char **charray);
char	*rl_gets(void);
char	**parse_line(char *line);

int	main(int argc, char **argv, char **envp)
{
	// char	**split_line;
	char	*line;
	// int		num;
	int		exec_ret;
	t_list	*cmd_list;

	(void)argc;
	(void)argv;
	(void)line;
	while (1)
	{
		line = rl_gets();
		// split_line = parse_line(line);
		// num = count_char_array(split_line);
		exec_ret = start_pipex(&cmd_list, envp);
		// free_char_array(split_line, 0);
		// free(line);
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
		exit(0);
	ft_fprintf(1, "%s\n", line);
	if (line && *line)
		// seeing if line is not is unnecessary because auf previous check,
		// leaving it in for later
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
