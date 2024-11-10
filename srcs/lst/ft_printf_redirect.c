/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:32:44 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/10 14:33:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_printf_redirect(void *redirect)
{
	t_redirect	*redir;
	int			count;

	redir = (t_redirect *)redirect;
	count = ft_printf("redirect:	%s\n", redir->filename->word);
	return (count);
}
