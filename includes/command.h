/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:21:58 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/09 10:41:43 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "redirect.h"

/* possible values for the `flags' field of command */
# define C_EXECUTE	(1 << 1) // needs to read from a pipe
# define C_COMMAND_BUILTIN 1 << 2
# define C_PIPE	1 << 3 // needs to read from a pipe
# define C_HERE_DOC	1 << 4 // needs to read from a here doc
# define C_OPEN_INFILE	1 << 5 // open file as infile
# define C_OPEN_OUT_TRUNC	1 << 6 // open output file truncated
# define C_OPEN_OUT_APP	1 << 7 // open output file for appending
# define C_LAST_PIPE	1 << 8 // execute command output to stdout

/* A structure which represents a command. */
typedef struct t_command {
	char	*cmd;		/* Zero terminated string. */
	t_redirect	*redirects;	/* Redirections associated with this command. */
	int	flags;		/* Flags associated with this command. */
} t_command;

#endif // !COMMAND_H
