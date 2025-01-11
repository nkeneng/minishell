

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = NULL;
	shell.exit_status = 0;
	init_envp(envp, &shell);
	ft_free_envp(shell.envp, shell.nb_env);
	return (shell.exit_status);
}
