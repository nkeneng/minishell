/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:04:39 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/22 10:34:34 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_error(t_word_list **word_list, char *str)
{
	errno = 2;
	ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", *str);
	free_word_list(word_list);
	return (errno);
}

int	syntax_error_unexpected_eof(t_word_list **word_list)
{
	errno = 2;
	ft_fprintf(2, "minishell: syntax error: unexpected end of file\n");
	free_word_list(word_list);
	return (errno);
}
