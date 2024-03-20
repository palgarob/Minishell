/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:31:42 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/20 23:00:04 by pepaloma         ###   ########.fr       */
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

