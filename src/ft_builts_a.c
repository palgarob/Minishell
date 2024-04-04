/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:00:02 by incalero          #+#    #+#             */
/*   Updated: 2024/04/04 16:44:34 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_change_var (t_command command)
{
	command.env_mini = NULL;
	return (0);
}

int ft_export(t_command command)
{
	char *var;
	size_t i;

	i = 0;
	var = command.arguments[1];
	printf("var = %s\n", var);
	while (var[i])
	{
		if (var[i] == '=')
			break;
		i++;
	}
	if (i >= ft_strlen(var))
	{
		printf ("minishell: %s: ", var);
		printf("command not found");
		return (-1);
	}
	else
		command.env_mini = ft_add_var(command, var);
/* 	i = 0;
	while(command.env_mini[i])
	{
		printf("%s\n", command.env_mini[i]);
		i++;
	} */
	ft_printf("POINTER24 %p \n", command.env_mini);
	return (0);
}

int ft_unset(t_command command)
{
	command.arguments[0] = NULL;

	
	printf("ha entrado en unset\n");
	return (0);
}

char **ft_dell(char **envcy, char **env_mini, int var_nbr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envcy[i])
	{
		if (i != var_nbr)
		{
			env_mini[j] = ft_strdup(envcy[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (env_mini);
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
	ft_printf("POINTER2 envp %p\n", envcpy);
	return (envcpy);
} 

char **ft_add_var(t_command command, char *var)
{
	int i;
	char **envcpy;
	int len;

	len = 0;
	i = 0;
	while (command.env_mini[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * (len + 2));
	if (!envcpy)
		return (NULL);
	while (command.env_mini[i])
	{
		envcpy[i] = ft_strdup(command.env_mini[i]);
		//printf("1i = %d s = %s\n", i, envcpy[i]);
		i++;
	}
	envcpy[i] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_free_array(command.env_mini);
	command.env_mini = NULL;
	/* i = 0;
	while (envcpy[i])
	{
		printf("2i = %d s = %s\n", i, envcpy[i]);
		i++;
	}  */
	ft_printf("POINTER23 envp %p\n", envcpy);
	return (envcpy);
}