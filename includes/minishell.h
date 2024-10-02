#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft_full.h"
# include "command.h"
# include "parsing.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_dlist
{
	char			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

//dlist
t_dlist	*ft_dlstnew(void *content);
t_dlist	*ft_dlstfirst(t_dlist *lst);
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new_node);

void	ft_printf_dlst(t_dlist **lst);
void	ft_dlstclear(t_dlist **lst);
t_dlist	*ft_createaddback(t_dlist **lst, void *content);
//PIPEX
//pipex.c
int		start_pipex(int argc, char *argv[], char *envp[]);
int		input_checker(int argc, char *arg);
int		pipheredoc(char *arg);
int		open_doc(char *file, int filekind);

//utils.c
int		free_char_array(char **array, int ret);
int		rperror(char *str);
int		here_doc(char *delim);

//path.c
char	*get_commpath(char *envp[], const char *command);
char	**get_paths(char *envp[]);
int		make_exec(char *arg, char *envp[]);
int		exec_to_stdout(char *arg, char **envp);
int		pipex(int argc, char **argv, char **envp, int curr);

//command.c
int		exec_to_stdout(char *arg, char **envp);
int		exec_command(char *command, char *envp[], int in_fd, int out_fd);
int		pipex(int argc, char **argv, char **envp, int curr);
#endif
