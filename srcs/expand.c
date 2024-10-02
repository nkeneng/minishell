/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:00:57 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/02 17:21:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_special_char_flags(char *word);
char	*clean_spaces(char *word);
int	isspecial(char sign);
char *split_on_special(char *word);
t_list	handle_split_on_pipe(char *word);

int	main(int argc, char **argv, char **envp)
{
	char	*word;
	int		flags;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		word = rl_gets();
		if (ft_strchr(word, ' ') != NULL || ft_strchr(word, '	') != NULL)
		{
			free(word);
			ft_fprintf(2, "you used several words");
			break ;
		}
		word = clean_spaces(word);
		flags = set_special_char_flags(word);
		free(word);
	}
	return (0);
}

//returns a malloced array containing all commands after splitting
t_list	**split_word(char *word)
{
	int		i;
	t_list	**start;
	t_list	*new;

	start = &new;
	if (!word || !*word)
		return (NULL);
	while (*word)
	{
		new = ft_lstnew(split_on_special(word));
		if (new != NULL)
			ft_lstadd_back(start, new);
		word++;
	}
	return (start);
}

//returns string from one special char to the next
char	*split_on_special(char *word)
{
	int	i;

	i = 1;
	if (isspecial(word[i]) > 0)
	{
		if (isspecial(word[i]) > 0)
		{
			word[i] = '\0';
			return (word);
		}
	}
	return (NULL);
}

char	*clean_spaces(char *word)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (word[i])
	{
		j = i + 1;
		if (word[i] == ' ' || word[i] == '\t')
		{
			while (word[j] == ' ' || word[j] == '\t')
				j++;
			if (j == i + 1)
				continue ;
			k = i + 1;
			while (word[j])
				word[k++] = word[j++];
		}
	}
	return (word);
}

int	isspecial(char sign)
{
	if (sign == '$')
		return (DOLLAR);
	if (sign == '~')
		return (TILDE);
	if (sign == '"')
		return (DQUOTE);
	if (sign == '\'')
		return (SQUOTE);
	return (0);
}

int	set_special_char_flags(char *word)
{
	int	flags;

	if (word[0] == '$')
		flags |= W_HASDOLLAR;
	if (strchr(word, '|') != NULL)
		handle_split_on_pipe(word);
	if (strchr(word, '~') != NULL)
	return (flags);
}

t_list	handle_split_on_pipe(char *word)
{
	char *pipe_pos;

	pipe_pos = strchr(word, '|');

}
