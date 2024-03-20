/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:34:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/20 13:13:34 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax(char **args)
{
	if (**args == '|')
		return (1);
	if (**ft_splitlast(args) == '|')
}

int	parse(char *line)
{
	char	**args;

	args = ft_split_shell(line, ' ');
	if (!args)
		return (1);
	if (syntax(args))
		return (perror(ERR_SYNTAX), ft_splitfree(args), 1);
	
}
