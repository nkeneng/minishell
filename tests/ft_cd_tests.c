/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:23:49 by stevennke         #+#    #+#             */
/*   Updated: 2024/10/02 22:04:02 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/minishell.h"

void setup(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ft_cd, change_to_home_directory, .init = setup)
{
    char *original_dir = getcwd(NULL, 0);
    char *home_dir = getenv("HOME");

    cr_assert(ft_cd(NULL) == 1);
    char *new_dir = getcwd(NULL, 0);
    cr_assert_str_eq(new_dir, home_dir);

    chdir(original_dir);
    free(original_dir);
    free(new_dir);
}

Test(ft_cd, change_to_specific_directory, .init = setup)
{
    char *original_dir = getcwd(NULL, 0);
    char *test_dir = "/tmp";

    cr_assert(ft_cd(test_dir) == 1);
    char *new_dir = getcwd(NULL, 0);
    cr_assert_str_eq(new_dir, test_dir);

    chdir(original_dir);
    free(original_dir);
    free(new_dir);
}

Test(ft_cd, error_nonexistent_directory, .init = setup)
{
    char *nonexistent_dir = "/this_directory_does_not_exist";

    cr_assert(ft_cd(nonexistent_dir) == -1);
    const char *error_msg = "chdir: No such file or directory\n";
    cr_assert_stderr_eq_str(error_msg);
}

Test(ft_cd, error_home_not_set, .init = setup)
{
    char *original_home = getenv("HOME");
    unsetenv("HOME");

    cr_assert(ft_cd(NULL) == -1);
    const char *error_msg = "HOME not set";
    cr_assert_stderr_eq_str(error_msg);

    if (original_home)
        setenv("HOME", original_home, 1);
}
