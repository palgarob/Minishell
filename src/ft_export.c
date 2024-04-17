/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:31:05 by incalero          #+#    #+#             */
/*   Updated: 2024/04/17 10:59:45 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_env_mini_order(t_command *command)
{
	int		i;
	char	*temp;
	char	**env;

	i = 0;
	env = command->shell->mini_env;
	while (env[i] && env[i + 1] != NULL)
	{
		if (ft_strncmp(env[i], env[i + 1], ft_str_equal_len(env[i])) > 0)
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

static void	ft_print_export(char **env, int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (env[i][j] && env[i][j] != '=')
		printf("%c", env[i][j++]);
	if (env[i][j] && env[i][j] == '=')
		printf("%c", env[i][j++]);
	if (ft_is_equal(env[i]) != 0)
	{
		printf("\"");
		while (env[i][j])
			printf("%c", env[i][j++]);
		printf("\"");
	}
}

static void	ft_export_env(t_command *command)
{
	int		i;
	char	**env_export;

	i = 0;
	env_export = ft_env_mini_order(command);
	while (env_export[i])
	{
		if (ft_strncmp("_=", env_export[i], 2) == 0)
			i++;
		ft_print_export(env_export, i);
		printf("\n");
		i++;
	}
}

int	ft_export(t_command *command)
{
	char	*var;
	int		nbr;
	int		i;

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
			if (ft_var_is_ok(var) == 0 && ft_var_exist(command, var) == 0)
				ft_add_var(command, var);
			i++;
		}
	}
	return (0);
}
