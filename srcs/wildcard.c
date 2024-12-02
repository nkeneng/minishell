/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:39:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/12/02 16:43:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int	main(void)
{
	DIR *dp;
	struct dirent *entry;
	char *path = "./";

	dp = opendir(path);
	if (dp != NULL)
	{
		entry = readdir(dp));
		while ((entry != NULL)
			printf("File Name: %s\n", entry->d_name);
			entry = readdir(dp));
	}
		closedir(dp);
}
