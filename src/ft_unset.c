/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:41:42 by incalero          #+#    #+#             */
/*   Updated: 2024/04/28 17:09:39 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command *command)
{
	char	*var;
	int		nbr;
	int		i;

	nbr = 0;
	i = 1;
	while (command->arguments[nbr])
		nbr++;
	while (command->arguments[i] && i < nbr)
	{
		var = command->arguments[i];
		command->shell->mini_env = ft_dell_var(command, var);
		i++;
	}
	return (0);
}
