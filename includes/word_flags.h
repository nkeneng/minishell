/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_flags.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:50:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/17 13:02:38 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_FLAGS
# define WORD_FLAGS

# define W_EXECUTE			2 // 1 << 1  needs to read from a pipe
# define W_COMMAND_BUILTIN  4 // 1 << 2
# define W_PIPE				8 // 1 << 3  needs to read from a pipe
# define W_HERE_DOC			16 // 1 << 4  needs to read from a here doc
# define W_OPEN_INFILE		32 // 1 << 5  open file as infile
# define W_OPEN_OUT_TRUNC	64 // 1 << 6  open output file truncated
# define W_OPEN_OUT_APP		128 // 1 << 7  open output file for appending
# define W_VAR				256 // 1 << 8  variable asignment
# define W_LAST_PIPE		512 // 1 << 9  execute command output to stdout
								//
# define W_HASDOLLAR	(1 << 10)	/* Dollar sign present. */
# define W_SQUOTED	(1 << 11)	/* Some signle quote character is present. */
# define W_DQUOTED	(1 << 12)	/* Some double quote character is present. */
# define W_ASSIGNMENT	(1 << 13)	/* This word is a variable assignment. */
# define W_SPLITSPACE	(1 << 14)	/* Split this word on " "*/
# define W_NOSPLIT	(1 << 15)	/* Do not perform word splitting on this word because ifs is empty string. */
# define W_EXPANDRHS	(1 << 16)	/* Expanding word in ${paramOPword} */
# define W_DONE		(1 << 30) /* nothing else to do here */


/* Possible values for the `flags' field of a WORD_DESC. */
//#define W_HASDOLLAR	(1 << 0)	/* Dollar sign present. */
//#define W_SQUOTED	(1 << 1)	/* Some signle quote character is present. */
//#define W_DQUOTED	(1 << 2)	/* Some double quote character is present. */
//#define W_ASSIGNMENT	(1 << 3)	/* This word is a variable assignment. */
//#define W_SPLITSPACE	(1 << 4)	/* Split this word on " " regardless of IFS */
//#define W_NOSPLIT	(1 << 5)	/* Do not perform word splitting on this word because ifs is empty string. */
//#define W_NOGLOB	(1 << 5)	/* Do not perform globbing on this word. */
//#define W_NOSPLIT2	(1 << 6)	/* Don't split word except for $@ expansion (using spaces) because context does not allow it. */
//#define W_TILDEEXP	(1 << 7)	/* Tilde expand this assignment word */
//#define W_DOLLARAT	(1 << 8)	/* UNUSED - $@ and its special handling */
//#define W_ARRAYREF	(1 << 9)	/* word is a valid array reference */
//#define W_NOCOMSUB	(1 << 10)	/* Don't perform command substitution on this word */
//#define W_ASSIGNRHS	(1 << 11)	/* Word is rhs of an assignment statement */
//#define W_NOTILDE	(1 << 12)	/* Don't perform tilde expansion on this word */
//#define W_NOASSNTILDE	(1 << 13)	/* don't do tilde expansion like an assignment statement */
//#define W_EXPANDRHS	(1 << 14)	/* Expanding word in ${paramOPword} */
//#define W_COMPASSIGN	(1 << 15)	/* Compound assignment */
//#define W_ASSNBLTIN	(1 << 16)	/* word is a builtin command that takes assignments */
//#define W_ASSIGNARG	(1 << 17)	/* word is assignment argument to command */
//#define W_HASQUOTEDNULL	(1 << 18)	/* word contains a quoted null character */
//#define W_DQUOTE	(1 << 19)	/* UNUSED - word should be treated as if double-quoted */
//#define W_NOPROCSUB	(1 << 20)	/* don't perform process substitution */
//#define W_SAWQUOTEDNULL	(1 << 21)	/* word contained a quoted null that was removed */
//#define W_ASSIGNASSOC	(1 << 22)	/* word looks like associative array assignment */
//#define W_ASSIGNARRAY	(1 << 23)	/* word looks like a compound indexed array assignment */
//#define W_ARRAYIND	(1 << 24)	/* word is an array index being expanded */
//#define W_ASSNGLOBAL	(1 << 25)	/* word is a global assignment to declare (declare/typeset -g) */
//#define W_NOBRACE	(1 << 26)	/* Don't perform brace expansion */
//#define W_COMPLETE	(1 << 27)	/* word is being expanded for completion */
//#define W_CHKLOCAL	(1 << 28)	/* check for local vars on assignment */
//#define W_FORCELOCAL	(1 << 29)	/* force assignments to be to local variables, non-fatal on assignment errors */
/* UNUSED		(1 << 30)	*/

#endif // !WORD_FLAGS
