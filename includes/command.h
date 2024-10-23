/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:21:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/23 14:50:48 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "redirect.h"

/* possible values for the `flags' field of command */
# define C_EXECUTE			2 // 1 << 1  needs to read from a pipe
# define C_COMMAND_BUILTIN  4 // 1 << 2
# define C_PIPE				8 // 1 << 3  needs to read from a pipe
# define C_HERE_DOC			16 // 1 << 4  needs to read from a here doc
# define C_OPEN_INFILE		32 // 1 << 5  open file as infile
# define C_OPEN_OUT_TRUNC	64 // 1 << 6  open output file truncated
# define C_OPEN_OUT_APP		128 // 1 << 7  open output file for appending
# define C_VAR				256 // 1 << 8  variable asignment
# define C_LAST_PIPE		512 // 1 << 9  execute command output to stdout

# define PIPE_OR_REDIR_MASK (C_PIPE | C_HERE_DOC | C_OPEN_INFILE | C_OPEN_OUT_TRUNC | C_OPEN_OUT_APP)
/* A structure which represents a command. */
typedef struct t_command {
	char	**cmd;		/* Zero terminated string. */
	t_redirect	*redirects;	/* Redirections associated with this command. */
	int	flags;		/* Flags associated with this command. */
} t_command;

#endif // !COMMAND_H
