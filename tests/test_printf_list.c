
#include "../../includes/minishell.h"

int main()
{
    t_list *head = NULL;
    t_command cmd1 = {"command1", NULL, 0};
    t_command cmd2 = {"command2", NULL, 0};
    t_command cmd3 = {"command3", NULL, 0};

    ft_lstadd_back(&head, ft_lstnew(&cmd1));
    ft_lstadd_back(&head, ft_lstnew(&cmd2));
    ft_lstadd_back(&head, ft_lstnew(&cmd3));

    ft_printf_lst(head, ft_printf_command);

    // Free the list after use

    return 0;
}
