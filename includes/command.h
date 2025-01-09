/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:21:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/09 12:35:17 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "redirect.h"

/* possible values for the `flags' field of command */
# define C_EXECUTE 2         // 1 << 1  needs to read from a pipe
# define C_BUILTIN 4         // 1 << 2
# define C_PIPE 8            // 1 << 3  needs to read from a pipe
# define C_HERE_DOC 16       // 1 << 4  needs to read from a here doc
# define C_OPEN_INFILE 32    // 1 << 5  open file as infile
# define C_OPEN_OUT_TRUNC 64 // 1 << 6  open output file truncated
# define C_OPEN_OUT_APP 128  // 1 << 7  open output file for appending
# define C_VAR 256           // 1 << 8  variable asignment
# define C_LAST_PIPE 512     // 1 << 9  execute command output to stdout
# define C_ONLY 1024         // 1 << 10  first command in a pipeline

# define PIPE_OR_REDIR_MASK (C_PIPE | C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP)

// enum used in is_builtin for a return value
enum	e_builtin
{
	EXIT_BUILTIN = 2,
	EXPORT_BUILTIN = 4,
	ENV_BUILTIN = 8,
	ECHO_BUILTIN = 16,
	CD_BUILTIN = 32,
	PWD_BUILTIN = 64,
	UNSET_BUILTIN = 128
};

/* A structure which represents a command. */
//**cmd;        /* NULL terminated array */                    
//*redirects; /* Redirections associated with this command. */ 
//flags;         /* Flags associated with this command. */     
typedef struct t_command
{
	char	**cmd;
	t_list	*redirects;
	int		flags;
}		t_command;

#endif // !COMMAND_H
