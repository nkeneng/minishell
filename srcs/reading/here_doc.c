/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:24:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/11 17:08:26 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: string expansion in here_doc

t_word_desc	*make_word_desc_from_line(char *line, int flags)
{
	t_word_desc	*item;

	item = ft_calloc(sizeof(t_word_desc), 1);
	if (!item)
	{
		free(item);
		return (NULL);
	}
	item->word = line;
	if (!item->word)
	{
		free_word_desc(&item);
		return (NULL);
	}
	item->flags = 0;
	return (item);
}

char	*expand_variables_in_line(char **line, t_shell *shell)
{
	t_word_desc	*item;

	item = make_word_desc_from_line(*line, 0);
	if (!item)
	{
		free(*line);
		return (NULL);
	}
	while (contains_more_vars(item))
	{
		if (!wd_expand_var(&item, shell))
		{
			free_word_desc(&item);
			free(*line);
			return (NULL);
		}
	}
	return (item->word);
}

//does heredoc
int	here_doc(char *delim, int expand, t_shell *shell)
{
	char	*line;
	int		delim_len;

	delim_len = ft_strlen(delim);
	while (1)
	{
		if (g_signal == SIGINT)
			return (130);
		// close(STDOUT_FILENO);
		// if (open("/dev/tty", O_WRONLY) != STDOUT_FILENO)
		// {
		// 	perror("Failed to reopen stdout");
		// 	exit(EXIT_FAILURE);
		// }
		// line = rl_gets("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (g_signal == SIGINT)
			return (130);
		if (!ft_strncmp(delim, line, delim_len) && \
			(line[delim_len] == '\n' || line[delim_len] == '\0'))
		{
			free(line);
			line = get_next_line(-1);
			// line = readline("> ");
			break ;
		}
		printf("%s", line);
		// ft_fprintf(STDOUT_FILENO, "%s", line);
		free(line);
		if (g_signal == SIGINT)
			return (130);
	}
	// close (STDIN_FILENO);
	return (0);
}
