
#include "../../includes/minishell.h"

t_list  *convert_word_list_to_list(t_word_list *word_list)
{
    t_list  *lst;
    t_command   *command;
    t_word_list *curr;
    t_list  *redirect_list;

    lst = NULL;
    curr = word_list;
    while (curr)
    {
        redirect_list = make_redirect_list(&curr);
        command = make_command_list(word_list, curr);
        command->redirects = redirect_list;
        ft_lstadd_back(&lst, ft_lstnew(command));
    }
    return (lst);
}