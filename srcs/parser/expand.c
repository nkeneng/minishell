/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/23 17:07:38 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// takes one item, checks if variables should be expanded, expands $variables
// from environment
// returns 0 if it failed the allocation
// returns 2 if syntax error
// returns -1 if it didn't need to change any items
// returns -2 if it expanded item
// returns -3 current elemented should be deleted (it expanded to empty str)
// instead of item
int	ft_expand_variable_name(t_word_desc *item, t_shell *shell)
{
	char	*varname;
	char	*value;
	char	*new_word;

	new_word = NULL;
	varname = ft_strchr(item->word, '$');
	if (item->flags & (WM_OPERATOR_MASK | W_SQUOTED) || !varname)
		return (-1);
	if (*varname && *(varname + 1) == '?')
	{
		value = ft_itoa(shell->exit_status);
		new_word = ft_strexchange(item->word, "$?", value);
		free(value);
	}
	else if (*varname)
	{
		varname = get_varname(++varname);
		if (!varname)
			return (0); // return a malloc error here?
		if (!(*varname))
			return (-1);
		value = envp_keytovalue(varname, shell, ft_strlen(varname));
		if (!(*value))
			return (-3);
		new_word = ft_strexchange(item->word, varname, value);
		free(varname);
	}
	if (!new_word)
		return (0); //malloc error
	free(item->word);
	item->word = new_word;
	item->flags += W_EXPANDED;
	return (-2);
}

void	exchange_in_word(t_word_desc *item, char *new_str, char *old_str, int flags)
{
	char	*new_word;
	int		var_till;

	var_till = ft_is_var_till(old_str);
	if (var_till == 0)
		return ;
	new_word = ft_strexchange(item->word, --old_str, ++var_till, new_str);
	if (!new_word)
	{
		free_word_desc(item);
		return ;
	}
	free(item->word);
	item->word = new_word;
	item->flags = flags;
}

t_word_desc	*wd_expand_var(t_word_desc *item, t_shell *shell)
{
	char	*value;
	int		var_till;
	char	*var_start;

	var_start = ft_strchr(item->word, '$');
	if (item->flags & (WM_OPERATOR_MASK | W_SQUOTED) || !var_start)
		return (item);
	if (*(var_start + 1) != '?')
	{
		var_till = ft_is_var_till(++var_start);
		if (var_till == 0)
			return (item);
		value = envp_keytovalue(var_start, shell, var_till);
		if (!value)
		{
			free_word_desc(item);
			return (NULL);
		}
		exchange_in_word(item, value, var_start, item->flags | W_EXPANDED);
		return (item);
	}
	value = ft_itoa(shell->exit_status);
	exchange_in_word(item, value, "$?", item->flags | W_EXPANDED);
	free(value);
	return (item);
}

// returns a valid variable name in an allocated string
// return "\0" empty string (local var), if no $ or var ended with length 0
// return NULL if allocation failed
char	*get_varname(char *varname)
{
	int		end;

	// varname = ft_strchr(str, '$');
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
