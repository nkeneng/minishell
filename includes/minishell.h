#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_full.h"
# include "expansion_macros.h"
# include "builtins.h"
# include "command.h"
# include "parsing.h"
# include "list.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// just for test cases
# include "dummy.h"

// PIPEX
// pipex.c
int					do_list(t_list **cmd_list, char **envp);
int					input_checker(int argc, char *arg);
int					pipheredoc(char *arg);
int					open_doc(char *file, int filekind);

// utils.c
int					free_char_array(char **array, int ret);
int					rperror(char *str);
int					count_char_array(char **charray);

//here_doc.c
int					here_doc(char *delim);

// path.c
char				*get_commpath(char *envp[], const char *command);
char				**get_paths(char *envp[]);
int					make_exec(t_command *command, char *envp[]);
int					pipex(char **envp, t_list *cmd_list);

// command.c
int					exec_command(t_command *command, char *envp[], int *fd);
int					exec_to_stdout(char **envp, t_command *command);
#endif
