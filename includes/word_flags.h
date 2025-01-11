/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_flags.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:50:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/01/11 05:12:09 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_FLAGS_H
# define WORD_FLAGS_H

# define W_EXECUTE 2         // 1 << 1  general execution
# define W_BUILTIN 4         // 1 << 2 is shell builtin function
# define W_PIPE 8            // 1 << 3  needs to read from a pipe
# define W_HERE_DOC 16       // 1 << 4  needs to read from a here doc
# define W_OPEN_INFILE 32    // 1 << 5  open file as infile
# define W_OPEN_OUT_TRUNC 64 // 1 << 6  open output file truncated
# define W_OPEN_OUT_APP 128  // 1 << 7  open output file for appending
# define W_AND 256           // 1 << 8  && operator
# define W_OR 512            // 1 << 9  || operator
# define W_ONLY 1024         // 1 << 10  First command in a pipeline.
# define W_SQUOTED 2048      // 1 << 11  Some single quote character is present.
# define W_DQUOTED 4096      // 1 << 12  Some double quote character is present.
# define W_ASSIGNMENT 8192   // 1 << 13  This word is a variable assignment.
# define W_SPLITSPACE 16384  // 1 << 14  curr word should be split from next
// because there had been a space at the end of the curr word or beginning of next
# define W_EXPANDRHS 65536     // 1 << 16  Expanding word in ${paramOPword}
# define W_VAR 131072          // 1 << 17  variable assignment
# define W_LAST 262144         // 1 << 18  execute command output to stdout
# define W_SUBSHELL 524288     // 1 << 19  ( ... ) subshell
# define W_NEEDCLOSBRC 1048576 // 1 << 20  need close brace
# define W_EXPANDED 8388608
// 1 << 23  word has been variable or tilde expanded
# define W_WORD_AND 268435456
// 1 << 28  word is not the operator but a word that needs to be anded
# define W_WORD_OR 536870912
// 1 << 29  word is not the operator but a word that needs to be ored
# define W_DONE 1073741824      // 1 << 30  nothing else to do here
# define W_HASDOLLAR 2147483648 // 1 << 31  Dollar sign present.

# define WM_REDIR_MASK (W_HERE_DOC | W_OPEN_INFILE | W_OPEN_OUT_TRUNC | W_OPEN_OUT_APP)
# define WM_OPERATOR_MASK (W_PIPE | W_AND | W_OR)
# define WM_OP_RE (WM_REDIR_MASK | WM_OPERATOR_MASK)
# define WM_SPLIT_AT_SPACES (W_SQUOTED | W_DQUOTED | WM_OPERATOR_MASK | WM_REDIR_MASK)

# define WM_DOUBLE_SIGN (W_HERE_DOC | W_AND | W_OR | W_OPEN_OUT_APP)
# define WM_SINGLE_SIGN (W_PIPE | W_OPEN_OUT_TRUNC | W_OPEN_INFILE | W_ASSIGNMENT)

#endif // !WORD_FLAGS
