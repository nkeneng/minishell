/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:24:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/20 15:09:06 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: string expansion in here_doc
char	*expand_line(t_shell *shell, char *line)
{
	t_word_desc	*container;
	char		*new_line;

	container = wd_make_word(line, ft_strlen(line), 0);
	if (!container)
		return (NULL);
	while (contains_more_vars(container))
		container = wd_expand_var(&container, shell);
	new_line = container->word;
	free(container);
	free(line);
	return (new_line);
}

//checkts if line is delimiter and frees line
//if this returns 1, line was the delimiter, should return from heredoc
int	line_is_delim(char *line, char *delim)
{
	int		delim_len;

	delim_len = ft_strlen(delim);
	if (!ft_strncmp(delim, line, delim_len) && \
		(line[delim_len] == '\n' || line[delim_len] == '\0'))
	{
		free(line);
		line = get_next_line(-1);
		return (1);
	}
	return (0);
}

//does heredoc
int	here_doc(t_shell *shell, char *delim, int flags)
{
	char	*line;

	reopen_stdin();
	while (1)
	{
		if (g_signal == SIGINT)
			return (130);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (g_signal == SIGINT)
			return (130);
		if (line_is_delim(line, delim))
			break ;
		if (!(flags & (W_DQUOTED | W_SQUOTED)))
			line = expand_line(shell, line);
		if (!line)
			return (rperror("malloc"));
		printf("%s", line);
		free(line);
		if (g_signal == SIGINT)
			return (130);
	}
	return (0);
}
