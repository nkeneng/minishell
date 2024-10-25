/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:57 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/25 10:59:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft_full.h"

// unsorted shellpromt
t_list	**convert_line_to_dlist(char *line);

// reading.c
char	*rl_gets(void);

//parse.c
t_list	*parse_input(char *line, char **envp);

// splitting.c 
t_word_list	*split_around(t_word_desc *input, char sign);
int			next_word_till(char *line, char sign);
int	next_word_till_metachar(char *line);

//flags.c
int	is_pipe_or_redirect(char *sign);
int	identify_word_type(t_word_desc *word);
int			get_flag_from_sign(char sign);
int	sign_to_flag(char *sign);
int	is_quote(char *sign);

//missing_close.c
int	missing_close_sign(char *line, char sign);
int	missing_close_bracket(char *line);

// word_list1.c
t_word_list	*make_word_list(char *line);
t_word_list	*wordlist_from_line(t_word_list *h, char *line, int size, int flag);

// word_list2.c
t_word_list	*word_list_addback(t_word_list *word_list, t_word_desc *word);
void		ft_printf_word_list(t_word_list *word_list);
void		*free_word_list(t_word_list **lst);

// word_list3.c
t_command *concat_to_t_command(t_word_list *head, t_word_list *curr);
t_list	*convert_to_command_lst(t_word_list *head);
t_word_list	*init_word_list(char *line);

//word_desc.c
t_word_desc *create_word(char *word, int flags);
void		free_word_desc(t_word_desc *word_desc);
t_word_desc	*make_word(const char *line, const int end, const int flag);
#endif // !PARSING_H
