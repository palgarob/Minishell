#include "minishell.h"

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

int ft_var_exist(t_command command , char *var)
{
	int i;
	int len;
	
	i = 0;
	len = ft_str_equal_len(var);
	while (command.shell->mini_env[i])
	{
		if (ft_strncmp(var, command.shell->mini_env[i], len) == 0)
		{
			free(command.shell->mini_env[i]);
			command.shell->mini_env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}


void ft_add_var(t_command command, char *var)
{
	int i;
	char **envcpy;
	int len;

	
	len = 0;
	i = 0;
	while (command.shell->mini_env[len])
		len++;
	printf ("env = %d\n", len);
	envcpy = (char **)malloc(sizeof(char *) * (len + 2));
	while (command.shell->mini_env[i])
	{
		envcpy[i] = ft_strdup(command.shell->mini_env[i]);
		i++;
	}
	printf ("var = %s\n",var);
	envcpy[i] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_splitfree(command.shell->mini_env);
	command.shell->mini_env = NULL;
	command.shell->mini_env = envcpy;
}


static char **ft_dell(char **env_mini, char **envcpy, int var_nbr)
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

	var_nbr = 0;
	len = 0;
	while (command.shell->mini_env[var_nbr])
	{
		if (ft_strncmp(var, command.shell->mini_env[var_nbr], ft_strlen(var)) == 0)
			break;
		var_nbr++;
	}
	if (!command.shell->mini_env[var_nbr])//si no encuentra coincidencia.
		return(command.shell->mini_env);
	while (command.shell->mini_env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * len);
	if (!envcpy)
		return (NULL);
	envcpy[len - 1] = NULL;
	ft_dell(command.shell->mini_env, envcpy, var_nbr);
	ft_splitfree(command.shell->mini_env);
	return (envcpy);
} 
