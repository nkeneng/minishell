
/* Possible values for the `flags' field of a WORD_DESC. */
# define W_HASDOLLAR	(1 << 0)	/* Dollar sign present. */
# define W_QUOTED	(1 << 1)	/* Some form of quote character is present. */
# define W_ASSIGNMENT	(1 << 2)	/* This word is a variable assignment. */
# define W_SPLITSPACE	(1 << 3)	/* Split this word on " " regardless of IFS */
# define W_NOSPLIT	(1 << 4)	/* Do not perform word splitting on this word because ifs is empty string. */
# define W_NOGLOB	(1 << 5)	/* Do not perform globbing on this word. */
# define W_NOSPLIT2	(1 << 6)	/* Don't split word except for $@ expansion (using spaces) because context does not allow it. */
# define W_TILDEEXP	(1 << 7)	/* Tilde expand this assignment word */
# define W_DOLLARAT	(1 << 8)	/* UNUSED - $@ and its special handling */
# define W_ARRAYREF	(1 << 9)	/* word is a valid array reference */
# define W_NOCOMSUB	(1 << 10)	/* Don't perform command substitution on this word */
# define W_ASSIGNRHS	(1 << 11)	/* Word is rhs of an assignment statement */
# define W_NOTILDE	(1 << 12)	/* Don't perform tilde expansion on this word */
# define W_NOASSNTILDE	(1 << 13)	/* don't do tilde expansion like an assignment statement */
# define W_EXPANDRHS	(1 << 14)	/* Expanding word in ${paramOPword} */
# define W_COMPASSIGN	(1 << 15)	/* Compound assignment */
# define W_ASSNBLTIN	(1 << 16)	/* word is a builtin command that takes assignments */
# define W_ASSIGNARG	(1 << 17)	/* word is assignment argument to command */
# define W_HASQUOTEDNULL	(1 << 18)	/* word contains a quoted null character */
# define W_DQUOTE	(1 << 19)	/* UNUSED - word should be treated as if double-quoted */
# define W_NOPROCSUB	(1 << 20)	/* don't perform process substitution */
# define W_SAWQUOTEDNULL	(1 << 21)	/* word contained a quoted null that was removed */
# define W_ASSIGNASSOC	(1 << 22)	/* word looks like associative array assignment */
# define W_ASSIGNARRAY	(1 << 23)	/* word looks like a compound indexed array assignment */
# define W_ARRAYIND	(1 << 24)	/* word is an array index being expanded */
# define W_ASSNGLOBAL	(1 << 25)	/* word is a global assignment to declare (declare/typeset -g) */
# define W_NOBRACE	(1 << 26)	/* Don't perform brace expansion */
# define W_COMPLETE	(1 << 27)	/* word is being expanded for completion */
# define W_CHKLOCAL	(1 << 28)	/* check for local vars on assignment */
# define W_FORCELOCAL	(1 << 29)	/* force assignments to be to local variables, non-fatal on assignment errors */
/* UNUSED		(1 << 30)	*/

/* Flags for the `pflags' argument to param_expand() and various
   parameter_brace_expand_xxx functions; also used for string_list_dollar_at */
#define PF_NOCOMSUB	0x01	/* Do not perform command substitution */
#define PF_IGNUNBOUND	0x02	/* ignore unbound vars even if -u set */
#define PF_NOSPLIT2	0x04	/* same as W_NOSPLIT2 */
#define PF_ASSIGNRHS	0x08	/* same as W_ASSIGNRHS */
#define PF_COMPLETE	0x10	/* same as W_COMPLETE, sets SX_COMPLETE */
#define PF_EXPANDRHS	0x20	/* same as W_EXPANDRHS */
#define PF_ALLINDS	0x40	/* array, act as if [@] was supplied */

/* Possible values for subshell_environment */
#define SUBSHELL_ASYNC	0x01	/* subshell caused by `command &' */
#define SUBSHELL_PAREN	0x02	/* subshell caused by ( ... ) */
#define SUBSHELL_COMSUB	0x04	/* subshell caused by `command` or $(command) */
#define SUBSHELL_FORK	0x08	/* subshell caused by executing a disk command */
#define SUBSHELL_PIPE	0x10	/* subshell from a pipeline element */
#define SUBSHELL_PROCSUB 0x20	/* subshell caused by <(command) or >(command) */
#define SUBSHELL_COPROC	0x40	/* subshell from a coproc pipeline */
#define SUBSHELL_RESETTRAP 0x80	/* subshell needs to reset trap strings on first call to trap */
#define SUBSHELL_IGNTRAP 0x100  /* subshell should reset trapped signals from trap_handler */

/* Possible values for command->flags. */
#define CMD_WANT_SUBSHELL  0x01	/* User wants a subshell: ( command ) */
#define CMD_FORCE_SUBSHELL 0x02	/* Shell needs to force a subshell. */
#define CMD_INVERT_RETURN  0x04	/* Invert the exit value. */
#define CMD_IGNORE_RETURN  0x08	/* Ignore the exit value.  For set -e. */
#define CMD_NO_FUNCTIONS   0x10 /* Ignore functions during command lookup. */
#define CMD_INHIBIT_EXPANSION 0x20 /* Do not expand the command words. */
#define CMD_NO_FORK	   0x40	/* Don't fork; just call execve */
#define CMD_TIME_PIPELINE  0x80 /* Time a pipeline */
#define CMD_TIME_POSIX	   0x100 /* time -p; use POSIX.2 time output spec. */
#define CMD_AMPERSAND	   0x200 /* command & */
#define CMD_STDIN_REDIR	   0x400 /* async command needs implicit </dev/null */
#define CMD_COMMAND_BUILTIN 0x0800 /* command executed by `command' builtin */
#define CMD_COPROC_SUBSHELL 0x1000
#define CMD_LASTPIPE	    0x2000
#define CMD_STDPATH	    0x4000	/* use standard path for command lookup */
#define CMD_TRY_OPTIMIZING  0x8000	/* try to optimize this simple command */
