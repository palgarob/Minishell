
#include "minishell.h"

static char **ft_env_mini_order(t_command *command)
{
	int i;
	char *temp;

	i = 0;
	char **env;
	env = command->shell->mini_env;
	while (env[i] && env[i + 1] != NULL)
	{
		if(ft_strncmp(env[i], env[i + 1], ft_str_equal_len(env[i])) > 0)
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	return (env);
}

static void ft_export_env(t_command *command)
{
	int i;
	int j;
	char **env_export;

	i = 0;
	env_export = ft_env_mini_order(command);
	while (env_export[i])
	{
		printf("declare -x ");
		j = 0;
		while (env_export[i][j] && env_export[i][j] != '=' /* && j < (int)ft_strlen(env_export[i]) */)
			printf("%c", env_export[i][j++]);
		if(env_export[i][j] && env_export[i][j] == '=')
			printf("%c",env_export[i][j++]);
		if (ft_is_equal(env_export[i]))
			printf("\"");
		while (env_export[i][j])
			printf("%c", env_export[i][j++]);
		if (ft_is_equal(env_export[i]))
			printf("\"");
		printf("\n");
		i++;
	}
	//ft_splitfree(env_export);
}

int	ft_export(t_command *command)
{
	char *var;
	int nbr;
	int i;

	nbr = 0;
	i = 1;
	while (command->arguments[nbr])
		nbr++;
	if (nbr == 1)
		ft_export_env(command);
	else
	{
		while (command->arguments[i] && i < nbr)
		{
			var = command->arguments[i];
			printf("var = %s\n", var);
			if (ft_var_is_ok(var) == 0 && ft_var_exist(command, command->arguments[i]) == 0)
				ft_add_var(command, var);
			i++;
		}
	}
	return (0);
}
