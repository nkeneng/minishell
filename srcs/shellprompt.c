/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellprompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:50 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/16 16:52:47 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rl_gets(void);
int	append_opts(char **split_line);
t_list	**convert_line_to_dlist(char *line);
void clean_line_whitespace(char *line);
t_command	*get_command(char *word, char **envp);

//deprecated
t_list	**parse_input(char *line, char **envp)
{
	t_list		**input;
	t_command	*command;
	t_list		*curr;
	char		**split_line;
	int			i;
	int			list_i;
	int			k;

	i = 0;
	clean_line_whitespace(line);
	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0])
	{
		free_char_array(split_line, 0);
		return (NULL);
	}
	while (split_line[i] && split_line[i + 1] != NULL)
	{
		command = get_command(split_line[i], envp);
		if (command)
		{
			if (!ft_lstcreateaddback(input, command))
				return (NULL);
		}
		else
			break ;
		k = append_opts(&split_line[i]);
		if (k)
		{
			free(command->cmd);
			command->cmd = split_line[i];
		}
		i += k;
		i++;
	}
	// only one command or last command
	if (split_line[i] && split_line[i + 1] == NULL)
		command = get_command(split_line[i], envp);
		if (command)
			input[list_i] = ft_lstnew(command);
	else
	{
		free_char_array(split_line, 0);
		return (NULL);
	}
	input = convert_line_to_dlist(line);
	return (input);
}

int	convert_pipes_to_flags(t_list **list)
{
	t_list		*curr;
	t_command	*command;

	curr = *list;
	while (curr->next)
	{
		command = (t_command *) curr->next->content;
		if (!ft_strncmp(command->cmd, "|", 2))
		{
			command = (t_command *) curr->content;
			command->flags &= C_PIPE;
			ft_lstdelone(curr->next, (void (*) (void *))ft_free_command);
		}
		curr = curr->next;
	}
}

int	append_opts(char **split_line)
{
	int	i;
	int	k;
	int	did_append;

	i = 0;
	k = i + 1;
	did_append = 0;
	while (split_line[k] && (split_line[k][0] == '-' || !ft_strchr("|<>&", split_line[k][0])))
	{
		ft_strappend(split_line[i], split_line[k]);
		did_append = 1;
		k++;
	}
	if (did_append == 0)
		return (0);
	return (k);
}

void	clean_line_whitespace(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (line[i])
	{
		j = i;
		if (line[i] == '\t')
			line[i] = ' ';
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (j > i + 1)
			ft_memmove(line + i, line + j, ft_strlen(line + i));
		i++;
	}
}

t_command	*get_command_flag(char *word, char **envp)
{
	t_command	*command;
	int			i;
	char		*commpath;

	command = malloc(sizeof(t_command));
	i = 1;
	commpath = get_commpath(get_paths(envp), word);
	if (commpath)
	{
		command->cmd = word;
		command->path = commpath;
		command->flags &= C_EXECUTE;
	}
	return (command);
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
