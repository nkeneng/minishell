/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:09:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/03 16:22:56 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The following is a brief description of the shell’s operation when it reads and
executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an
	argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules 
	described in Quoting. These tokens are separated by metacharacters. 
	Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the 
	expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the 
	redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status 
	(see Exit Status).
*/

t_list	*parse_input(char *line, char **envp)
{
	/* t_list		*lst; */
	t_word_list	*word_list_head;

	(void)envp;
	//optionally open script if strstr(line, ".sh") and read from it
	while (missing_close_sign(line, '\'')) // this doesn't work
		ft_strjoin(line, rl_gets()); // can't free readline allocated things!!
	word_list_head = make_word_list(line);
	if (!word_list_head)
		return (NULL);
	// ft_printf_word_list(word_list_head);
	// convert_word_list_to_list(word_list_head);
	/* lst = convert_to_command_lst(word_list_head); */
	/* ft_printf_lst(lst, ft_printf_command); */
	free_word_list(&word_list_head);
	return (NULL);
}
