/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:09:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 11:10:49 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
1. Reads its input from a file (see Shell Scripts), from a string supplied as an
	argument to the -c invocation option (see Invoking Bash), 
	or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules 
	described in Quoting. These tokens are separated by metacharacters. 
	Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the 
	expanded tokens into lists of filenames (see Filename Expansion) 
	and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the 
	redirection operators and their operands from the argument list.
*/

t_list	*parse_input(char *line, t_shell *shell)
{
	t_word_list	*word_list_head;
	t_list		*lst;

	(void)shell;
	errno = 0;
	word_list_head = make_word_list(line, shell);
	if (!word_list_head)
		return (NULL);
	lst = convert_word_list_to_list(word_list_head);
	return (lst);
}
