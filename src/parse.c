/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:34:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 03:26:50 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**parse(char *line)
{
	char	**args;

	args = ft_split_shell(line);
	if (!args)
		return (NULL);
	if (syntax(args))
		return (perror(ERR_SYNTAX), ft_splitfree(args), NULL);
	return (args);
	
}
