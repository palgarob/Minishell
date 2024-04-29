/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:22:51 by incalero          #+#    #+#             */
/*   Updated: 2024/04/22 13:49:03 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_str_equal_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	ft_is_equal(char *s)
{
	if ((ft_str_equal_len(s) == ft_strlen (s)) && ft_strlen(s) > 1)
		return (0);
	if (ft_strlen(s) == 1 && s[0] != '=')
		return (0);
	else
		return (1);
}

int	ft_var_is_ok(char *s)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (s[j] != '\0' && s[j] != '=')
		j++;
	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (printf("export: '%s': not a valid identifier\n", s), 1);
	while (s[i] && i < j)
	{
		if (s[0] != '_' && !ft_isalnum(s[0]))
			return (printf("export: '%s': not a valid identifier\n", s), 1);
		i++;
	}
	return (0);
}

int	ft_var_exist(t_command *command, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_str_equal_len(var);
	while (command->shell->mini_env[i])
	{
		if (ft_strncmp(var, command->shell->mini_env[i], len) == 0
			&& len == (int)ft_str_equal_len(command->shell->mini_env[i]))
		{
			free(command->shell->mini_env[i]);
			command->shell->mini_env[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_add_var(t_command *command, char *var)
{
	int		i;
	char	**envcpy;
	int		len;

	len = 0;
	i = 0;
	while (command->shell->mini_env[len])
		len++;
	envcpy = (char **)malloc(sizeof(char *) * (len + 2));
	while (command->shell->mini_env[i])
	{
		envcpy[i] = ft_strdup(command->shell->mini_env[i]);
		i++;
	}
	envcpy[i] = ft_strdup(var);
	envcpy[i + 1] = NULL;
	ft_splitfree(command->shell->mini_env);
	command->shell->mini_env = NULL;
	command->shell->mini_env = envcpy;
}
