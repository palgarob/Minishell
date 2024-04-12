#include "minishell.h"

void	ft_unset(t_command command)
{
	char *var;
	int nbr;
	int i;
	
	nbr = 0;
	i = 1;
	while (command.arguments[nbr])
		nbr++;
	while (command.arguments[i] && i < nbr)
	{
		var = command.arguments[i];
		command.shell->mini_env = ft_dell_var (command, var);
		i++;
	}
	exit(0);
}