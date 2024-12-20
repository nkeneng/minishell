/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:24:07 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/20 14:44:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: string expansion in here_doc

char	*expand_line(t_shell *shell, char *line)
{
	t_word_desc	*container;

	container = wd_make_word(line, ft_strlen(line), 0);
	if (!container)
		return (NULL);
	while (contains_more_vars(container))
		container = wd_expand_var(&container, shell);
	line = container->word;
	free(container);
	return (line);
}

//does heredoc
int	here_doc(t_shell *shell, char *delim, int flags)
{
	char	*line;
	int		delim_len;
	int		expand;

	delim_len = ft_strlen(delim);
	reopen_stdin();
	expand = !(flags & (W_DQUOTED | W_SQUOTED));
	while (1)
	{
		if (g_signal == SIGINT)
			return (130);
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
			break ;
		}
		(void) shell;
		if (expand)
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
