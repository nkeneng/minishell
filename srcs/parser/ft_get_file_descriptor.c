
#include "../../includes/minishell.h"

// takes a line and returns file descriptor if it's a number between 0 and 1024
// returns -1 if it's not a valid file descriptor
int	ft_get_file_descriptor(char *str)
{
	int	i;
	int	fd;

	i = 0;
	while (str[i])
	{
		if (i > 4)
			return (-1);
		if (ft_whitespace_sepreator(str[i]))
			break ;
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	fd = ft_strtoimax(str, NULL, 10);
	if (fd > 1024)
		return (-1);
	return (fd);
}

