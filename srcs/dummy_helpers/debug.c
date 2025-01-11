/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:14:47 by admin             #+#    #+#             */
/*   Updated: 2025/01/11 05:14:48 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void	debug_log(const char *format, ...)
{
	va_list	args;
	int		fd;

	fd = open("debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	va_start(args, format);
	vdprintf(fd, format, args);
	va_end(args);
	close(fd);
}
