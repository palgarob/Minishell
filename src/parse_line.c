/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:34:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/23 21:00:34 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	stract_operator(char *line, char ***split_ptr)
{
	int		position;
	char	*arg;

	position = 1;
	if (*line == '<' || *line == '>')
	{
		if (line[position] == *line)
			position += 1;
	}
	arg = ft_substr(line, 0, position);
	if (!arg)
		return (perror(0), 0);
	if (ft_splitadd(arg, split_ptr))
		return (free(arg), 0);
	return (position);
}

static int	stract_argument(char *line, char ***split_ptr)
{
	int		position;
	char	*arg;
	int		quote;

	position = 0;
	while (!is_metachar(line[position]) && line[position] != 32
		&& line[position] && line[position] != 9)
	{
		if (line[position] == '"' || line[position] == '\'')
		{
			quote = line[position++];
			while (line[position] != quote)
				if (!line[position++])
					return (write(1, "Syntax error\n", 13), 0);
		}
		position++;
	}
	arg = ft_substr(line, 0, position);
	if (!arg)
		return (perror(0), 0);
	if (ft_splitadd(arg, split_ptr))
		return (free(arg), 0);
	return (position);
}

static char	**split_line(char *line)
{
	char	**split;
	int		position;

	split = NULL;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else
		{
			if (is_metachar(*line))
				position = stract_operator(line, &split);
			else
				position = stract_argument(line, &split);
			if (!position)
			{
				if (split)
					ft_splitfree(split);
				return (NULL);
			}
			line += position;
		}
	}
	return (split);
}

static int	syntax(char **args)
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

char	**parse_line(char *line)
{
	char	**args;

	args = split_line(line);
	if (!args)
		return (NULL);
	if (syntax(args))
		return (write(STDERR_FILENO, "Syntax error\n", 13),
			ft_splitfree(args), NULL);
	return (args);
}
