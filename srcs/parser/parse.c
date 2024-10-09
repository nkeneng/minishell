/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:09:04 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/09 12:28:46 by lmeubrin         ###   ########.fr       */
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
	t_list	**list;
	t_word_list	*word_list;
	//optionally open script if strstr(line, ".sh") and read from it
	word_list = split_into_words(line);
}

//Breaks the input into words and operators, obeying the quoting rules 
//described in Quoting. These tokens are separated by metacharacters. 
//Alias expansion is performed by this step (see Aliases).
t_word_list	split_into_words(char *line)
{
	t_word_list	*word_list;
	t_word_list	*current_word;
	char *word;
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*args;
	char	*line;
	int		exec_ret;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = rl_gets();
		if (!missing_close_sign(line, '\''))
			ft_strappend(line, rl_gets());
		args = parse_input(line, envp);
		num = ft_lstsize(args);
		exec_ret = do_list(&args, envp);
	}
	ft_lstclear(&args, 0);
	return (exec_ret);
}
