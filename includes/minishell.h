#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_full.h"
# include "structs.h"
# include "builtins.h"
# include "command.h"
# include "expansion_macros.h"
# include "list.h"
# include "parsing.h"
# include "pipex.h"
# include "redirect.h"
//# include "globals.h"
# include "functions_to_remove_later.h"
# include "signals.h"
# include "word_flags.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "〘🐚〙: "

// GLOBALS
extern volatile sig_atomic_t	g_signal;

// dlist
t_dlist							*ft_dlstnew(void *content);
t_dlist							*ft_dlstfirst(t_dlist *lst);
int								ft_dlstsize(t_dlist *lst);
t_dlist							*ft_dlstlast(t_dlist *lst);
void							ft_dlstadd_back(t_dlist **lst,
									t_dlist *new_node);

void							ft_printf_dlst(t_dlist **lst);
void							ft_dlstclear(t_dlist **lst);
t_dlist							*ft_createaddback(t_dlist **lst, void *content);

// PIPEX
// pipex.c
int								do_list(t_list **cmd_list, char **envp);
int								start_pipex(t_list **cmd_list, t_shell *shell);
int								input_checker(int argc, char *arg);
int								pipheredoc(char *arg);
int								open_doc(t_shell *shell, char *file,
									int filekind);

// utils.c
int								free_char_array(char **array, int ret);
int								rperror(char *str);
int								count_char_array(char **charray);

// checkdir.c
int								checkdir(char *path);

// here_doc.c
int								here_doc(t_shell *shell, char *delim,
									int flags);

// file_redirection.c
int								has_flags(t_command *command, int wordmask_in_or_out);
int								handle_redirects(t_shell *shell,
									t_command *command, int wordmask_in_or_out);
void							reopen_stdout(void);
void							reopen_stdin(void);

// path.c
char							*get_commpath(char *envp[],
									const char *command);
char							**get_paths(char *envp[]);
int								make_exec(t_command *command, char *envp[]);

// command.c
int								exec_command(t_command *command, t_env **envp,
									int *fd);
int								pipex(t_shell *shell, t_list **cmd_list);

// init_envp.c
void							init_envp(char **env, t_shell *shell);

// init_shell.c
t_shell							*init_shell(char **env);

// ft_free_shell.c
void							ft_free_shell(t_shell *shell);
void							ft_free_envp(t_env *envp, int nb_env);

// SIGNALS
// signal.c
void							signal_dfl(int signum);
void							signal_ign(int signum);
void							init_signals_heredoc(void);
void							init_signals(void);
void							signal_handler(int signum);
void							init_signals_noninteractive(void);
void							signal_handler_noninteractive(int signum);
void							signal_handler_when_children(int signum);
void							init_signals_when_children(void);

// reading
// reading.c
char							*rl_gets(char *prompt);
// new utility and library functions
// ft_strexchange_within.c
char							*ft_exchange_within(char *original, int from,
									int to, char *exch_with);
#endif
