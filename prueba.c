#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	line = readline("prompt: ");
	printf("input: %s\n", line);
	free(line);
	return (0);
}
