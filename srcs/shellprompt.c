/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/07 08:56:47 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

char	*rl_gets(void);
char	**parse_line(char *line);
t_list	**convert_line_to_dlist(char *line);
t_list	**parse_input(char *line);

int	main(int argc, char **argv, char **envp)
{
	t_list	**split_line;
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
		split_line = parse_input(line);
		num = ft_lstsize(*split_line);
		exec_ret = start_pipex(num, split_line, envp);
		ft_lstclear(split_line, 0);
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
	curr = ft_lstnew((void *)split_line[0]);
	start = &curr;
	i = 1;
	while (split_line[i])
	{
		new = ft_lstnew((void *)split_line[i++]);
		curr->next = new;
		curr = new;
	}
	return (start);
}

//splits input line into array of strings !old , replace
char	**parse_line(char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	return (split_line);
}

// input promt for shell
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

