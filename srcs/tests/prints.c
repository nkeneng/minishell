/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:24:41 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/16 17:59:16 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_flag_name(int flag)
{
	if (flag & W_EXECUTE)
		ft_printf("W_EXECUTE\n");
	if (flag & W_COMMAND_BUILTIN)
		ft_printf("W_COMMAND_BUILTIN\n");
	if (flag & W_PIPE)
		ft_printf("W_PIPE\n");
	if (flag & W_HERE_DOC)
		ft_printf("W_HERE_DOC\n");
	if (flag & W_OPEN_INFILE)
		ft_printf("W_OPEN_INFILE\n");
	if (flag & W_OPEN_OUT_TRUNC)
		ft_printf("W_OPEN_OUT_TRUNC\n");
	if (flag & W_OPEN_OUT_APP)
		ft_printf("W_OPEN_OUT_APP\n");
	if (flag & W_VAR)
		ft_printf("W_VAR\n");
	if (flag & W_LAST)
		ft_printf("W_LAST_PIPE\n");
	if (flag & W_HASDOLLAR)
		ft_printf("W_HASDOLLAR\n");
	if (flag & W_SQUOTED)
		ft_printf("W_SQUOTED\n");
	if (flag & W_DQUOTED)
		ft_printf("W_DQUOTED\n");
	if (flag & W_ASSIGNMENT)
		ft_printf("W_ASSIGNMENT\n");
	if (flag & W_SPLITSPACE)
		ft_printf("W_SPLITSPACE\n");
	if (flag & W_NOSPLIT)
		ft_printf("W_NOSPLIT\n");
	if (flag & W_EXPANDRHS)
		ft_printf("W_EXPANDRHS\n");
	if (flag & W_AND)
		ft_printf("W_AND\n");
	if (flag & W_OR)
		ft_printf("W_OR\n");
	if (flag & W_DONE)
		ft_printf("W_DONE\n");
	if (flag & 0)
		ft_printf("no flag\n");
	if (flag & W_WORD_AND)
		ft_printf("W_WORD_AND\n");
	if (flag & W_WORD_OR)
		ft_printf("W_WORD_OR\n");
	if (flag & W_EXPANDED)
		ft_printf("W_EXPANDED\n");
}
