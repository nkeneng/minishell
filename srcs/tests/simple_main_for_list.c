/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_main_for_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:02:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/18 10:03:57 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_list_head;
	t_list		*lst;
	char		line[] = "Hello|word | space";
	// int		exec_ret;
	(void)argc;
	(void)argv;
	(void)envp;
	word_list_head = make_word_list_new(line);
	ft_printf_word_list(word_list_head);
	lst = convert_to_command_lst(word_list_head);
	ft_printf_lst(lst, ft_printf_command);
	free_word_list(&word_list_head);
	ft_lstclear(&lst, ft_free_command);
	// exec_ret = do_list(&wordlist, envp);
	return (0);
	// return (exec_ret);
}
