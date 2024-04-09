/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:00:02 by incalero          #+#    #+#             */
/*   Updated: 2024/04/09 12:56:39 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

size_t ft_str_equal_len(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break;
		i++;
	}
	return (i);
}

int ft_is_equal (char *s)
{
	if ((ft_str_equal_len(s) == ft_strlen (s)) && ft_strlen(s) > 1)
		return (0);
	if (ft_strlen(s) == 1 && s[0] != '=')
		return (0);
	else 
		return (1);
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
		if (ft_is_equal(env_export[i]))
			printf("\"");
		while (env_export[i][j])
			printf("%c", env_export[i][j++]);
		if (ft_is_equal(env_export[i]))
			printf("\"");
		printf("\n");
		i++;
	}
	ft_free_array(env_export);
}

int ft_var_is_ok(char *s)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (s[i] && s[j] != '=')
		j++;
	while (s[i] && i < j)
	{
		if (!((s[0] == '_') || (s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')))
		{
			printf("minishell: export: '%s': not a valid identifier\n", s);
			return (0);
		}
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9') || (s[i] == '=')))
		{
			printf("minishell: export: '%s': not a valid identifier\n", s);
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_var_exist(t_command *command)
{
	char *var;
	int i;
	int len;
	
	i = 0;
	var = command->arguments[1];
	len = ft_str_equal_len(var);
	while (command->env_mini[i])
	{
		if (ft_strncmp(var, command->env_mini[i], len) == 0)
		{
			free(command->env_mini[i]);
			command->env_mini[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
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
		printf("var = %s\n", var);
		if (ft_var_is_ok(var) == 0)
			return (0);
		if (ft_var_exist(command) == 1)
			return (0);
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

/* void ft_add_var(t_command *command, char *var, char *var_tipe)
{
	int i;
	char ***envcpy;
	int len;

	len = 0;
	printf ("len = %d\n", len);
	i = 0;
	while (command->env_var[len] != NULL)
		len++;
	printf ("len = %d\n", len);
	envcpy = (char ***)malloc(sizeof(char **) * (len + 2));
	while (command->env_var[i])
	{
		envcpy[i] = (char **)malloc(sizeof(char *) * 3);
		envcpy[i][0] = ft_strdup(command->env_var[i][0]);
		envcpy[i][1] = ft_strdup(command->env_var[i][1]);
		envcpy[i][2] = NULL;
		i++;
	}
	envcpy[i] = (char **)malloc(sizeof(char *) * 3);
	envcpy[i][0] = ft_strdup(var_tipe);
	envcpy[i][1] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_free_array_triple(command->env_var);
	command->env_var = envcpy;
} */

void ft_add_var (t_command *command, char *var)
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
