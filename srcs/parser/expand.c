/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/24 13:32:25 by lmeubrin         ###   ########.fr       */
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
	new_word = ft_strexchange((*item)->word, old, var_till, new);
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
	value = envp_keytovalue(start, shell, var_till);
	if (!value)
	{
		free_str(&((*item)->word));
		return (*item);
	}
	exchange_in_word(item, value, start, (*item)->flags | W_EXPANDED);
	return ((*item));
}

t_word_desc	*wd_expand_var(t_word_desc *(*item), t_shell *shell)
{
	char	*value;
	char	*var_start;

	var_start = ft_strchr((*item)->word, '$');
	if ((*item)->flags & (WM_OPERATOR_MASK | W_SQUOTED) || !var_start)
		return ((*item));
	if (*(var_start + 1) != '?')
	{
		return (exch_vars_from_env(item, shell, var_start));
	}
	value = ft_itoa(shell->exit_status);
	if (!value)
		return (free_word_desc(item));
	exchange_in_word(item, value, "?", (*item)->flags | W_EXPANDED);
	free(value);
	return ((*item));
}

//UNUSED !!!!11
// returns a valid variable name in an allocated string
// return "\0" empty string (local var), if no $ or var ended with length 0
// return NULL if allocation failed
char	*get_varname(char *varname)
{
	int		end;

	ft_printf("varname: %s\n", varname);
	if (!varname)
		return ("\0");
	if ((*varname))
	{
		end = ft_is_var_till(varname);
		if (end == 0)
			return ("\0");
		varname = ft_substr(varname, 0, end);
		if (!varname)
			return (NULL);
	}
	return (varname);
}

char	*envp_keytovalue(char *key, t_shell *shell, int keylen)
{
	int		i;
	t_env	*env;

	i = 0;
	env = shell->envp;
	while (i < shell->nb_env)
	{
		if (!ft_strncmp(key, env[i].key, keylen))
			return (env[i].value);
		i++;
	}
	return (NULL);
}
