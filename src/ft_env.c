#include "minishell.h"

void	ft_env(t_command command)
{
	int i;
	i = 0;
	
	printf("%p\n", command.shell->mini_env);
	while(command.shell->mini_env[i])
	{
		if (ft_is_equal(command.shell->mini_env[i]) == 0)
			i++;
		else
			printf("%s\n", command.shell->mini_env[i]);
		i++;
	}
	exit(0);
}