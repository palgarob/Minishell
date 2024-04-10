/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:00:02 by incalero          #+#    #+#             */
/*   Updated: 2024/04/10 11:06:42 by incalero         ###   ########.fr       */
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

char **ft_env_mini_order(t_shell *shell)
{
	int i;
	char *temp;

	i = 0;
	char **env;
	env = ft_get_env(shell->mini_env);
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

void ft_export_env(t_shell *shell)
{
	int i;
	int j;
	char **env_export;

	i = 0;
	env_export = ft_env_mini_order(shell);
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
	while (s[j] != '\0' && s[j] != '=')
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

int ft_var_exist(t_command *command , char *var)
{
	int i;
	int len;
	
	i = 0;
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

int ft_export(t_shell *shell)
{
	char *var;
	int nbr;
	int i;

	nbr = 0;
	i = 1;
	while (shell->first_command.arguments[nbr])
		nbr++;
	if (nbr == 1)
		ft_export_env(shell);
	else
	{
		while (shell->first_command.arguments[i] && i < nbr)
		{
			var = shell->first_command.arguments[i];
			if (ft_var_is_ok(var) == 0)
				return (0);
			if (ft_var_exist(shell, shell->first_command.arguments[i]) == 1)
				return (0);
			ft_add_var(shell, var);
			i++;
		}
	}
	return (0);
}

void ft_unset(t_shell *shell)
{
	char *var;
	int nbr;
	int i;
	
	nbr = 0;
	i = 1;
	while (shell->first_command.arguments[nbr])
		nbr++;
	while (shell->first_command.arguments[i] && i < nbr)
	{
		var = shell->first_command.arguments[i];
		shell->mini_env = ft_dell_var (shell, var);
		i++;
	}
}

char **ft_dell(char **mini_env, char **envcpy, int var_nbr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini_env[i])
	{
		if (i != var_nbr)
		{
			envcpy[j] = ft_strdup(mini_env[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (envcpy);
}

char **ft_dell_var(t_shell *shell, char *var)
{
	int var_nbr;
	int len;
	char **envcpy;

	var_nbr = 0;
	len = 0;
	while (shell->mini_env[var_nbr])
	{
		if (ft_strncmp(var, shell->mini_env[var_nbr], ft_strlen(var)) == 0)
			break;
		var_nbr++;
	}
	if (!shell->mini_env[var_nbr])//si no encuentra coincidencia.
		return(shell->mini_env);
	while (shell->mini_env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * len);
	if (!envcpy)
		return (NULL);
	envcpy[len - 1] = NULL;
	ft_dell(shell->mini_env, envcpy, var_nbr);
	ft_free_array(shell->mini_env);
	return (envcpy);
} 

void ft_add_var (t_shell *shell, char *var)
{
	int i;
	char **envcpy;
	int len;

	len = 0;
	i = 0;
	while (shell->mini_env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * (len + 2));
	while (shell->mini_env[i])
	{
		envcpy[i] = ft_strdup(shell->mini_env[i]);
		i++;
	}
	envcpy[i] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_free_array(shell->mini_env);
	shell->mini_env = NULL;
	shell->mini_env = envcpy;
}
