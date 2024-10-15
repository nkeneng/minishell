/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:57 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/15 16:19:05 by lmeubrin         ###   ########.fr       */
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

// word_list1.c
t_word_list	*make_word_list(char *line);
t_word_list	*split_at_pipes(char *line);

// word_list2.c
t_word_list	*word_list_addback(t_word_list *word_list, t_word_desc *word);
t_word_desc *create_word(char *word, int flags);
void		ft_printf_word_list(t_word_list *word_list);
void		free_word_desc(t_word_desc *word_desc);
void		free_word_list(t_word_list **lst);

// word_list3.c
t_command *concat_to_t_command(t_word_list *head, t_word_list *curr);
t_list	*convert_to_command_lst(t_word_list *head);

#endif // !PARSING_H
