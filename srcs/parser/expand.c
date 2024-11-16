/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:17 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 16:34:19 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_varname(char *str);
char	*envp_keytovalue(char *key, t_shell *shell);

// takes one item, checks if variables should be expanded, expands $variables
// from environment
// returns 0 if it failed the allocation
// returns 2 if syntax error
// returns -1 if it didn't need to change any items
// returns -2 if it expanded item
// instead of item
int	ft_expand_variable_name(t_word_desc *item, t_shell *shell)
{
	char	*varname;
	char	*value;

	(void) shell;
	if (item->flags & (WM_OPERATOR_MASK | W_SQUOTED))
		return (-1);
	varname = get_varname(item->word);
	if (!varname)
		return (0); // return a malloc error here?
	if (!(*varname))
		return (-1);
	value = envp_keytovalue(varname, shell);
	ft_printf("VALUE: -%s-\n", value);
	// ft_strexchange(item->word, varname, value);
	free(varname);
	return (-2);
}

//function to exchange the string to_replace and its preceeding $ with new_string
// in the original string and frees the original
// returns a malloced string or NULL if allocation failed
// char	*ft_strexchange(char *original, char *to_replace, char *new_str)
// {
// 	int	len_to_replace;
// 	int	len_original;
//
// 	len_to_replace = ft_strlen(to_replace);
// 	len_original = ft_strlen(original);
//
// 	return (NULL);
// }

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
		ft_printf("varname: %s\n", varname);
	}
	return (varname);
}

char	*envp_keytovalue(char *key, t_shell *shell)
{
	int	i;
	int	keylen;
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
