/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:00:02 by incalero          #+#    #+#             */
/*   Updated: 2024/04/05 17:06:58 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (*s1 && *s2 && --n)
		{
			if (*s1 != *s2)
				return ((unsigned char)*s1 - (unsigned char)*s2);
			s1++;
			s2++;
		}
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
	return (0);
}

int ft_strequallen(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break;
		i++;
	}
	return (i);
}

char **ft_env_mini_order(t_command *command)
{
	int i;
	char *temp;

	i = 0;
	char **env;
	env = ft_get_env(command->env_mini);
	while (env[i] && env[i + 1] != NULL)
	{
		if(ft_strncmp(env[i], env[i + 1], ft_strequallen(env[i])) > 0)
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

void ft_export_env(t_command *command)
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
		while (env_export[i][j] && env_export[i][j] != '=')
			printf("%c", env_export[i][j++]);
		if(env_export[i][j] && env_export[i][j] == '=')
			printf("%c",env_export[i][j++]);
		printf("\"");
		while (env_export[i][j])
			printf("%c", env_export[i][j++]);
		printf("\"\n");
		i++;
	}
	ft_free_array(env_export);
}

int ft_change_var (t_command command)
{
	command.env_mini = NULL;
	return (0);
}

int ft_export(t_command *command)
{
	char *var;
	int nbr;

	nbr = 0;
	while (command->arguments[nbr])
		nbr++;
	if (nbr == 1)
		ft_export_env(command);
	else
	{
		var = command->arguments[1];
		ft_add_var(command, var);
	}
	return (0);
}

int ft_unset(t_command *command)
{
	command->arguments[0] = NULL;

	
	printf("ha entrado en unset\n");
	return (0);
}

char **ft_dell(char **env_mini, char **envcpy, int var_nbr)
{
	int i;
	int j;

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

char **ft_dell_var(t_command command, char *var)
{
	int var_nbr;
	int len;
	char **envcpy;
	char *var_equal;

	var_nbr = 0;
	len = 0;
	var_equal = ft_strjoin(var, "=");
	while (command.env_mini[var_nbr])
	{
		if (ft_strncmp(var_equal, command.env_mini[var_nbr], ft_strlen(var_equal)) == 0)
			break;
		var_nbr++;
	}
	if (!command.env_mini[var_nbr])//si no encuentra coincidencia.
		return(free(var_equal), command.env_mini);
	free(var_equal);
	while (command.env_mini[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * len);
	if (!envcpy)
		return (NULL);
	envcpy[len - 1] = NULL;
	ft_dell(command.env_mini, envcpy, var_nbr);
	ft_free_array(command.env_mini);
	return (envcpy);
} 

void ft_add_var(t_command *command, char *var)
{
	int i;
	char **envcpy;
	int len;

	len = 0;
	i = 0;
	while (command->env_mini[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * (len + 2));
	while (command->env_mini[i])
	{
		envcpy[i] = ft_strdup(command->env_mini[i]);
		i++;
	}
	envcpy[i] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_free_array(command->env_mini);
	command->env_mini = NULL;
	command->env_mini = envcpy;
}
