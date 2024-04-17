/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:00 by incalero          #+#    #+#             */
/*   Updated: 2024/04/17 11:23:27 by incalero         ###   ########.fr       */
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

static int	ft_get_pwd(t_command *command, char *var)
{
	char	cwd[1024];
	char	*new;
	char	*pwd;

	new = getcwd(cwd, sizeof(cwd));
	if (ft_var_exist(command, var) == 0)
		ft_add_var(command, var);
	pwd = ft_strjoin("PWD=", new);
	if (ft_var_exist(command, pwd) == 0)
		ft_add_var(command, pwd);
	return (0);
}

static int	ft_change_directory(t_command *command, const char *directory)
{
	char	cwd[1024];
	char	*var;

	var = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	if (directory != NULL && directory[0] == '-')
	{
		if (chdir(ft_get_cd (command, "OLDPWD=")) != 0)
			return (perror(""), 1);
		ft_get_pwd(command, var);
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
	else if (directory == NULL || directory[0] == '~')
	{
		if (chdir(ft_get_cd (command, "HOME=")) != 0)
			return (perror(""), 1);
		ft_get_pwd(command, var);
	}
	else
	{
		if (chdir(directory) != 0)
			return (write (1, "minishell: cd: ", 15), perror((char *)directory), 1);
		ft_get_pwd(command, var);
	}
	return (0);
}

int	ft_cd(t_command *command)
{
	if (command->arguments[1] == NULL)
		ft_change_directory(command, NULL);
	else
		ft_change_directory(command, command->arguments[1]);
	return (0);
}
