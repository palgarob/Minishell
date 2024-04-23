/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:42:54 by incalero          #+#    #+#             */
/*   Updated: 2024/04/23 13:56:48 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_dell_oldpwd(t_shell *shell, char *var)
{
	int		var_nbr;
	int		len;
	char	**envcpy;

	var_nbr = 0;
	len = 0;
	while (shell->mini_env[var_nbr])
	{
		if (ft_strncmp(var, shell->mini_env[var_nbr], ft_strlen(var)) == 0)
			break ;
		var_nbr++;
	}
	if (!shell->mini_env[var_nbr])
		return (shell->mini_env);
	while (shell->mini_env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * len);
	if (!envcpy)
		return (NULL);
	envcpy[len - 1] = NULL;
	ft_dell(shell->mini_env, envcpy, var_nbr);
	ft_splitfree(shell->mini_env);
	return (envcpy);
}

char	**ft_dell(char **env_mini, char **envcpy, int var_nbr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_mini[i])
	{
		if (i != var_nbr)
		{
			envcpy[j] = ft_strdup(env_mini[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (envcpy);
}

char	**ft_dell_var(t_command *command, char *var)
{
	int		var_nbr;
	int		len;
	char	**envcpy;
	char	**env;

	var_nbr = 0;
	len = 0;
	env = command->shell->mini_env;
	while (env[var_nbr])
	{
		if (ft_strncmp(var, env[var_nbr], ft_strlen(var)) == 0)
			break ;
		var_nbr++;
	}
	if (!env[var_nbr])
		return (env);
	while (env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * len);
	if (!envcpy)
		return (NULL);
	envcpy[len - 1] = NULL;
	ft_dell(env, envcpy, var_nbr);
	ft_splitfree(env);
	return (envcpy);
}

int	ft_change_directory(t_command *command, const char *directory)
{
	char	cwd[1024];
	char	*var;

	var = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	if (chdir(directory) != 0)
		return (free (var), write (1, "minishell: cd: ", 15),
			perror((char *)directory), 1);
	ft_get_pwd(command, var);
	return (free (var), 0);
}

int	ft_get_pwd(t_command *command, char *var)
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
	free (pwd);
	return (0);
}
