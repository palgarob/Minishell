/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:04:48 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/23 11:56:46 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *command)
{
	int	i;

	i = 1;
	if (command->arguments[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(command->arguments[1], "-n", 2) == 0)
		i++;
	while (command->arguments[i])
	{
		ft_print_str(command->arguments[i]);
		if (command->arguments[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(command->arguments[1], "-n", 2))
		printf("\n");
	return (0);
}
