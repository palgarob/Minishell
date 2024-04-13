/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:04:48 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/13 17:36:48 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command command)
{
	int i;

	i = 1;
	if (ft_strncmp(command.arguments[1], "-n", 2) == 0)
			i++;
	while (command.arguments[i])
	{
		ft_print_str(command.arguments[i]);
		if (command.arguments[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(command.arguments[1], "-n", 2))
		printf("\n");
	return (0);
}
