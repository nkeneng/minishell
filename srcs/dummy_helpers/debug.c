#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void debug_log(const char *format, ...)
{
	va_list args;
	int fd;

	fd = open("debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return;

	va_start(args, format);
	vdprintf(fd, format, args);
	va_end(args);

	close(fd);
}