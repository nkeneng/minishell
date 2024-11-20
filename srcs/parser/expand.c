/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 17:59:43 by lmeubrin         ###   ########.fr       */
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

	(void) shell;
	if (item->flags & (WM_OPERATOR_MASK | W_SQUOTED))
		return (-1);
	varname = get_varname(item->word);
	if (!varname)
		return (0); // return a malloc error here?
	if (!(*varname))
		return (-1);
	value = envp_keytovalue(varname, shell);
	if (!(*value))
		return (-3);
	new_word = ft_strexchange(item->word, varname, value);
	free(varname);
	if (!new_word)
		return (0); //malloc error
	free(item->word);
	item->word = new_word;
	item->flags += W_EXPANDED;
	return (-2);
}

// returns a valid variable name in an allocated string
// return "\0" empty string (local var), if no $ or var ended with length 0
// return NULL if allocation failed
char	*get_varname(char *str)
{
	char	*varname;
	int		end;

	varname = ft_strchr(str, '$');
	if (!varname)
		return ("\0");
	if ((*varname))
	{
		end = ft_is_var_till(++varname);
		if (end == 0)
			return ("\0");
		varname = ft_substr(varname, 0, end);
		if (!varname)
			return (NULL);
	}
	return (varname);
}

char	*envp_keytovalue(char *key, t_shell *shell)
{
	int		i;
	int		keylen;
	t_env	*env;

	i = 0;
	keylen = ft_strlen(key);
	env = shell->envp;
	while (i < shell->nb_env)
	{
		if (!ft_strncmp(key, env[i].key, keylen))
			return (env[i].value);
		i++;
	}
	return ("\0");
}
