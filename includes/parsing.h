/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:57 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/09 12:24:21 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft_full.h"

// unsorted shellpromt
char	*rl_gets(void);
t_list	*parse_input(char *line, char **envp);
t_list	**convert_line_to_dlist(char *line);

//missing_close.c
int	missing_close_sign(char *line, char sign);
int	missing_close_bracket(char *line);

#endif // !PARSING_H
