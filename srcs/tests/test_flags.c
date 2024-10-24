/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:18:33 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/24 12:44:15 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/functions_to_remove_later.h"

int	main(int argc, char *argv[])
{
	int	flag;

	if (argc != 2)
		printf("usage: ./a.out <your sign or string starting with sign here>");
	flag = sign_to_flag(argv[1]);
	print_flag_name(flag);
}
