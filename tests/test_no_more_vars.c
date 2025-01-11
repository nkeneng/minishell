
#include "../../includes/minishell.h"

//main to test contains_no_more_vars
volatile sig_atomic_t	g_signal = 0;
int main()
{
    t_word_desc items[] = {
        { .word = "~ $? $?", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "$HOME $USER $empty $ $? $?", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "some words here $", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "some $ words ~ $HOME", .flags = 1},
        { .word = "some $ ~ $$ $ $", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "no vars here", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "$", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "$var$", .flags = W_EXPANDED | W_DQUOTED },
        { .word = "var$   var", .flags = W_EXPANDED | W_DQUOTED }
    };

    for (int i = 0; i < 9; i++) {
        int result = contains_no_more_vars(&items[i]);
        printf("Test case %d: %s\n", i + 1, result ? "Contains more vars" : "No more vars");
		ft_printf_word_desc(&items[i]);
    }

    return 0;
}
