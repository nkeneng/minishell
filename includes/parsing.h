/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:42:57 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/11/18 15:50:24 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft_full.h"

//quotes.c
t_word_desc	*remove_quotes(t_word_desc *word);

//vars.c
int	ft_is_var_till(char *line);
int	ft_is_special(char c);
void	ft_is_var_name(t_word_desc *word);

//ft_strexchange.c
char	*ft_strexchange(char *original, char *to_replace, char *new_str);

//expand.c
int	ft_expand_variable_name(t_word_desc *item, t_shell *shell);
char	*get_varname(char *str);
char	*envp_keytovalue(char *key, t_shell *shell);

//wl_expansion.c
int	wl_expand_list(t_word_list **word_list, t_shell *shell);
t_word_list	*expand_and_split(t_word_list **word_list, t_word_list *curr, t_shell *shell);

//ft_get_file_descriptor.c
int	ft_get_file_descriptor(char *str);

// unsorted shellpromt
t_list	**convert_line_to_dlist(char *line);

// syntax_error.c
int	syntax_error(t_word_list **word_list, char *str);

// reading.c
char	*rl_gets(void);

//cleanup
void	clean_line_whitespace(t_word_desc *obj);
void	wl_clean_whitespace(t_word_list *lst);

//parse.c
t_list	*parse_input(char *line, t_shell *shell);

// splitting.c 
t_word_list	*split_around(t_word_desc *input);
int			next_word_till(char *line, char sign);
int	next_word_till_metachar(char *line);

//spaces.c
int	memmove_whitespaces_to_space(char *line);
int	ft_remove_spaces(char *line);
int	wd_remove_whitespace(t_word_desc *item);
int	clean_whitespaces_to_space(t_word_desc *item);
int	ft_whitespace_seperator(char *line);

//split_at_space.c
t_word_list	*split_at_spaces(t_word_list *item);
t_word_list	*word_list_ft_split(char *line, int	flags);

//flags.c
int	flag_correctly_delimeted(t_word_desc *item);
int	is_pipe_or_redirect(char *sign);
int	identify_word_type(t_word_desc *word);
int	sign_to_flag(char *sign);
int	is_quote(char *sign);

//flags_setting.c
void	assign_flag(t_word_list *list);
void	assign_operator_till_end(t_word_list *list, int flag);

//missing_close.c
int	missing_close_sign(char *line, char sign);
int	missing_close_bracket(char *line);

// make_word_list.c
t_word_list	*make_word_list(char *line, t_shell *shell);
int	wl_identify_words(t_word_list **word_list);
int	wl_split_on_whitesp(t_word_list **word_list, t_shell *shell);
t_word_list	*wl_from_line(t_word_list *h, char *line, int size, int flag);
t_word_list	*split_element_at_wh(t_word_list **word_list, t_word_list *item);

// word_list_methods.c
t_word_list	*wl_init(char *line);
t_word_list	*wl_addback(t_word_list *word_list, t_word_desc *word);
void		ft_printf_word_list(t_word_list *word_list);
void		*free_word_list(t_word_list **lst);
t_word_list	*wl_insert(t_word_list *word_list, t_word_desc *word);

// word_list_methods2.c
t_redirect	*wl_to_redirect(t_word_list **head, t_word_list *to_unlink);
t_word_list	*wl_add_node(t_word_list **head, char *line, int begin, int len);
t_word_list	*wl_delone(t_word_list **head, t_word_list *to_remove);
t_word_list	*wl_insert_instead(t_word_list *new_lst, t_word_list *old);
t_word_list	*wl_insert_word_list(t_word_list *new_lst, t_word_list *after);
t_word_desc	*wl_unlink(t_word_list **head, t_word_list *to_unlink);

// word_list_methods3.c
t_word_list	*wl_from_line(t_word_list *h, char *line, int size, int flag);
t_word_list	*wl_remove_whitespace_element(t_word_list **head, t_word_list *curr);

//word_desc.c
void	ft_free_word_desc(void *word_desc);
int		ft_printf_word_desc(void *word_desc);
void		free_word_desc(t_word_desc *word_desc);
t_word_desc	*wd_make_word(const char *line, const int end, const int flag);
#endif // !PARSING_H
