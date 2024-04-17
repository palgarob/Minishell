/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:07 by incalero          #+#    #+#             */
/*   Updated: 2024/04/17 09:29:50 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *command)
{
	int		i;
	char	*var;

	i = 0;
	var = "_=/usr/bin/env";
	if (ft_var_exist(command, var) == 0)
		ft_add_var(command, var);
	while (command->shell->mini_env[i])
	{
		if (ft_is_equal(command->shell->mini_env[i]) == 0)
			i++;
		else
			printf("%s\n", command->shell->mini_env[i]);
		i++;
	}
	return (0);
}
