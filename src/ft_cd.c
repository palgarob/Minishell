/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:00 by incalero          #+#    #+#             */
/*   Updated: 2024/04/23 13:56:44 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_cd(t_command *command, char *var)
{
	int		j;
	int		i;
	char	*cd;
	char	*env;

	i = 0;
	j = 0;
	while (command->shell->mini_env[i])
	{
		if (ft_strncmp(command->shell->mini_env[i], var, ft_strlen(var)) == 0)
			break ;
		i++;
	}
	if (i == (int)ft_splitlen(command->shell->mini_env))
		return (printf("minishell: %s: %s not set\n",
				command->arguments[0], var), NULL);
	env = command->shell->mini_env[i];
	while (env[j])
	{
		if (env[j] == '=')
			break ;
		j++;
	}
	cd = ft_substr(env, j + 1, ft_strlen(env));
	return (cd);
}

static int	ft_change_old_directory(t_command *command)
{
	char	cwd[1024];
	char	*var;
	char	*cd;

	var = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	cd = ft_get_cd(command, "OLDPWD");
	if (cd == 0)
		return (free(cd), free(var), 1);
	else
		chdir(cd);
	ft_get_pwd(command, var);
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	return (free(cd), free(var), 0);
}

static int	ft_change_home_directory(t_command *command)
{
	char	cwd[1024];
	char	*var;
	char	*home;

	var = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	home = ft_get_cd (command, "HOME");
	chdir(home);
	ft_get_pwd(command, var);
	return (free (home), free (var), 0);
}

int	ft_cd(t_command *command)
{
	if (command->arguments[1] == NULL)
		ft_change_home_directory(command);
	else if (ft_strncmp(command->arguments[1], "-", 1) == 0)
		ft_change_old_directory(command);
	else
		return (ft_change_directory(command, command->arguments[1]));
	return (0);
}
