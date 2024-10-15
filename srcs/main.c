/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:13:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/15 16:58:18 by snkeneng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*g_envp;
	t_list	*tmp;
	t_shell	shell;

	(void)argc;
	(void)envp;
	(void)argv;
	(void)shell;
	int i = 0;
	while (envp[i])
	{
		if (envp[i+1] == NULL)
			ft_printf("%s\n", envp[i]);
		i++;
	}
	init_envp(envp, &g_envp);
	shell.envp = g_envp;
	/* ft_export("hello=world", &shell); */
	tmp = ft_lstlast(g_envp);
	ft_printf("Key : %s\n Value : %s\n", ((t_env *)tmp->content)->key,
		((t_env *)tmp->content)->value);
	return (EXIT_SUCCESS);
}
