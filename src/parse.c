/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:34:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 01:00:09 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax(char **args)
{
	int	i;

	if (**args == '|' || is_metachar(**ft_splitlast(args)))
		return (1);
	i = -1;
	while (args[++i])
		if ((*args[i] == '<' || *args[i] == '>') && is_metachar(*args[i + 1]))
			return (1);
	return (0);
}

int	insert_value(char **args, int j)
{
	char	*value;
	char	*var_name;
	int		k;
	int		i;
	
	k = j + 1;
	i = 0;
	while ((*args)[k] != ' ' && (*args)[k] != 0
			&& (*args)[k] != '\'' && (*args)[k] != '"')
	{
		k++;
		i++;
	}
	var_name = ft_substr(*args, j + 1, i);
	if (!var_name)
		return (perror(0), 1);
	value = ft_getenv(var_name);
	free(var_name);
	if (!value)
		return (1);
	if (ft_strins(args, j, k, value))
		return (free(value), 1);
	free(value);
	return (0);
}

int	access_values(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\'')
			{
				j++;
				while (args[i][j++] != '\'')
					;
			}
			if (args[i][j] == '$' && args[i][j + 1] != ' '
					&& args[i][j + 1] != '?' && args[i][j + 1] != 0)
			{
				if (insert_value(&(args[i]), j))
					return (1);
			}
		}
	}
	return (0);
}

int	trim_quotes(char **args)
{
	int		j;
	int		i;
	
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '"')
			{
				ft_strins(&args[i], j, j + 1, "");
				while (args[i][j] != '"')
					j++;
				ft_strins(&args[i], j, j + 1, "");
			}
			if (args[i][j] == '\'')
			{
				ft_strins(&args[i], j, j + 1, "");
				while (args[i][j] != '\'')
					j++;
				ft_strins(&args[i], j, j + 1, "");
			}	
		}
	}
	return (0);
}

char	**parse(char *line)
{
	char	**args;

	args = ft_split_shell(line);
	if (!args)
		return (NULL);
	if (syntax(args))
		return (perror(ERR_SYNTAX), ft_splitfree(args), NULL);
	if (access_values(args) || trim_quotes(args))
		return (ft_splitfree(args), NULL);
	return (args);
	
}
