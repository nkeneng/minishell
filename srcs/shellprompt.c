/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/02 16:46:10 by lmeubrin         ###   ########.fr       */
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
t_list	**convert_line_to_dlist(char *line);
t_list	**parse_input(char *line);

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
		ft_fprintf(1, "%s\n", line);
		split_line = parse_line(line);
		num = count_char_array(split_line);
		exec_ret = start_pipex(num, split_line, envp);
		free_char_array(split_line, 0);
	}
	return (exec_ret);
}

t_list	**parse_input(char *line)
{
	t_list	**input;

	input = convert_line_to_dlist(line);
	return (input);
}

//splits line and puts it into a double linked list, returns head of dlist
t_list	**convert_line_to_dlist(char *line)
{
	t_list	**start;
	t_list	*curr;
	t_list	*new;
	char	**split_line;
	int		i;

	split_line = ft_split(line, ' ');
	curr = ft_dlstnew((void *)split_line[0]);
	start = &curr;
	i = 1;
	while (split_line[i])
	{
		new = ft_dlstnew((void *)split_line[i++]);
		curr->next = new;
		curr = new;
	}
	return (start);
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
