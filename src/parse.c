/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:34:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/20 20:46:50 by pepaloma         ###   ########.fr       */
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

int	insert_value2(char **args, int j, int k, char *value)
{
	char	*left;
	char	*right;

	left = ft_substr(*args, 0, j);
	if (!left)
		return (perror(0), 1);
	right = ft_substr(*args, k, ft_strlen(&(*args)[k]));
	if (!right)
		return (free(left), perror(0), 1);
	free(*args);
	*args = ft_strjoin(left, value);
	free(left);
	if (!*args)
		return (perror(0), 1);
	*args = ft_strjoin_gnl(*args, right);
	free(right);
	if (!*args)
		return (perror(0), 1);
	return (0);
}

int	insert_value(char **args, int j)
{
	char	*value;
	char	*var_name;
	int		k;
	
	k = j + 1;
	while ((*args)[k] != ' ' && (*args)[k++] != 0)
		;
	var_name = ft_substr(*args, j + 1, k);
	if (!var_name)
		return (perror(0), 1);
	value = getenv(var_name);
	if (!value)
	{
		value = (char *)malloc(sizeof(char) * 1);
		*value = 0;
	}
	value = ft_strdup(value);
	free(var_name);
	if (!value)
		return (perror(0), 1);
	if (insert_value2(args, j, k, value))
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
			if (args[i][j] == '$' && args[i][j + 1] != ' ' && args[i][j + 1] != '?' && args[i][j + 1] != 0)
			{
				if (insert_value(&(args[i]), j)) //Hay que hacer un jota plus
					return (1);
			}
		}
	}
//	ft_printf("%s\n", *args);
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
	if (access_values(args))
		return (ft_splitfree(args), NULL);
	return (args);
	
}
