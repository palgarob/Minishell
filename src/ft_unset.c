/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:41:42 by incalero          #+#    #+#             */
/*   Updated: 2024/04/17 09:42:07 by incalero         ###   ########.fr       */
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
		command->shell->mini_env = ft_dell_var (command, var);
		i++;
	}
	return (0);
}
