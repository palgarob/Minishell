/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:34:21 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/04 13:39:57 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	insert_value(char **split_line, int j, char **mini_env)
{
	char	*value;
	char	*var_name;
	int		k;
	int		i;

	k = j + 1;
	i = 0;
	while ((*split_line)[k] != ' ' && (*split_line)[k] != 0
			&& (*split_line)[k] != '\'' && (*split_line)[k] != '"')
	{
		k++;
		i++;
	}
	var_name = ft_substr(*split_line, j + 1, i);
	if (!var_name)
		return (perror(0), 1);
	value = ft_getenv(var_name, mini_env);
	free(var_name);
	if (!value)
		return (1);
	if (ft_strins(split_line, j, k, value))
		return (free(value), 1);
	free(value);
	return (0);
}

int	expand_parameters(char **split_line, bool ignore_quotes, char **mini_env)
{
	int		j;

	j = -1;
	while ((*split_line)[++j])
	{
		if ((*split_line)[j] == '\'' && !ignore_quotes)
		{
			j++;
			while ((*split_line)[j++] != '\'')
				;
		}
		if ((*split_line)[j] == '$' && (*split_line)[j + 1] != '?')
		{
			
		}
		if ((*split_line)[j] == '$' && (*split_line)[j + 1] != ' '
				&& (*split_line)[j + 1] != '?' && (*split_line)[j + 1] != 0)
		{
			if (insert_value(split_line, j, mini_env))
				return (1);
		}
	}
	if (!ignore_quotes)
		trim_quotes(split_line);
	return (0);
}
