
void clean_line_whitespace(char *line);
#include <stdio.h>
#include "../../includes/minishell.h"

void clean_line_whitespace(char *line)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (line[i])
	{
		j = i;
		if (line[i] == '\t')
			line[i] = ' ';
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (j > i + 1)
			ft_memmove(line + i, line + j, ft_strlen(line + i));
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("before\n%s\n", argv[1]);
	clean_line_whitespace(argv[1]);
	printf("after\n%s\n", argv[1]);
}

