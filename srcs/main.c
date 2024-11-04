/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/22 15:53:06 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*tmp;
	t_shell	shell;
	int		i;

	(void)argc;
	(void)argv;
	(void)shell;
	(void)tmp;
	(void)i;
	i = 0;
	shell.envp = NULL;
	init_envp(envp, &shell);
	ft_export("export", &shell);
	ft_export("export PATH=world 1223=dsds hello=world", &shell);
	ft_printf("number of env variables: %d\n", shell.nb_env);
	while (i < shell.nb_env)
	{
		ft_printf("key: %s, value: %s\n", shell.envp[i].key, shell.envp[i].value);
		i++;
	}
	return (EXIT_SUCCESS);
}
