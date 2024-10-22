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
	ft_export("hello=world", &shell);
	ft_export("PATH=world", &shell);
	ft_printf("number of env variables: %d\n", shell.nb_env);
	// tmp = shell.envp;
	// while (tmp)
	// {
	// 	ft_printf("Key : %s\n Value : %s\n", ((t_env *)tmp->content)->key,
	// 		((t_env *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }
	/* tmp = ft_lstlast(g_envp); */
	/* ft_printf("Key : %s\n Value : %s\n", ((t_env *)tmp->content)->key, */
	/* 	((t_env *)tmp->content)->value); */
	return (EXIT_SUCCESS);
}
