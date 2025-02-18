/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/03 13:40:36 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exchange_in_word(t_word_desc **item, char *new, char *old, int flags)
{
	char	*new_word;
	int		var_till;

	if (*(old) == '?')
		var_till = 1;
	else
	{
		var_till = ft_is_var_till(old);
		if (var_till == 0)
			return ;
	}
	new_word = ft_strexchange((*item)->word, var_till, new);
	if (!new_word)
	{
		free_word_desc(item);
		return ;
	}
	free((*item)->word);
	(*item)->word = new_word;
	(*item)->flags = flags;
}

t_word_desc	*exch_vars_from_env(t_word_desc **item, t_shell *shell, char *start)
{
	int		var_till;
	char	*value;

	var_till = ft_is_var_till(++start);
	if (var_till == 0)
		return ((*item));
	value = envp_keytovalue(start, shell->envp, var_till);
	if (!value)
		exchange_in_word(item, "", start, (*item)->flags | W_EXPANDED);
	else
		exchange_in_word(item, value, start, (*item)->flags | W_EXPANDED);
	return ((*item));
}

// takes a word_desc element and exchanges the ~ with the home directory
// ~- with OLDPWD
// ~+ with PWD
t_word_desc	*exchange_tile(t_word_desc **item, t_shell *shell)
{
	char	*value;
	char	*new_string;
	int		len;

	len = 2;
	if ((*item)->word[1] == '-')
		value = envp_keytovalue("OLDPWD", shell->envp, 6);
	else if ((*item)->word[1] == '+')
		value = envp_keytovalue("PWD", shell->envp, 3);
	else
	{
		value = envp_keytovalue("HOME", shell->envp, 4);
		len = 1;
	}
	if (value)
	{
		new_string = ft_exchange_within((*item)->word, 0, len, value);
		free((*item)->word);
		(*item)->word = new_string;
	}
	(*item)->flags |= W_EXPANDED;
	return (*item);
}

// gets called by expand_and_split 
// returns a wl element that had its variables replaced
t_word_desc	*wd_expand_var(t_word_desc *(*item), t_shell *shell)
{
	char	*value;
	char	*var_start;

	var_start = ft_strchr((*item)->word, '$');
	if (!var_start)
		var_start = ft_strchr((*item)->word, '~');
	if ((*item)->flags & (WM_OPERATOR_MASK | W_SQUOTED) || !var_start)
		return ((*item));
	if (*(var_start) == '~')
		return (exchange_tile(item, shell));
	if (*(var_start + 1) != '?')
		return (exch_vars_from_env(item, shell, var_start));
	value = ft_itoa(shell->exit_status);
	if (!value)
		return (free_word_desc(item));
	exchange_in_word(item, value, "?", (*item)->flags | W_EXPANDED);
	free(value);
	return ((*item));
}

char	*envp_keytovalue(char *key, t_env *env, int keylen)
{
	int		i;

	i = 0;
	while (env[i].key)
	{
		if (!ft_strncmp(key, env[i].key, keylen))
			return (env[i].value);
		i++;
	}
	return (NULL);
}
