#include "minishell.h"

int	ft_env(t_command *command)
{
	int i;
	i = 0;
	
	while(command->shell->mini_env[i])
	{
		if (ft_is_equal(command->shell->mini_env[i]) == 0)
			i++;
		else
			printf("%s\n", command->shell->mini_env[i]);
		i++;
	}
	return (0);
}
