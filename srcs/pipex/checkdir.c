/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:40:29 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/19 20:05:46 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// check if the path is a directory. return 0 if not a dir, 126 if dir
int	checkdir(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
	{
		perror("stat");
		return (EXIT_FAILURE);
	}
	if (S_ISDIR(buffer.st_mode))
	{
		ft_fprintf(2, "%s: Is a directory\n", path);
		return (126);
	}
	return (0);
}
