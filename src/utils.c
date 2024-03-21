/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:31:42 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 03:24:26 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar(char c)
{
	if (
		c == '|' || c == '<' || c == '>'
	)
		return (true);
	return (false);
}

char	*ft_getenv(char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
	{
		value = (char *)malloc(sizeof(char) * 1);
		if (!value)
			return (perror(0), NULL);
		*value = 0;
	}
	value = ft_strdup(value);
	if (!value)
		return (perror(0), NULL);
	return (value);
}

int	trim_quotes(char **args)
{
	int		j;
	int		i;
	int		quote;
	
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '"' || args[i][j] == '\'')
			{
				quote = args[i][j];
				ft_strins(&args[i], j, j + 1, "");
				while (args[i][j] != quote)
					j++;
				ft_strins(&args[i], j, j + 1, "");
			}
		}
	}
	return (0);
}
