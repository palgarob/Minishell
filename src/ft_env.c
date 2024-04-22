/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:29:07 by incalero          #+#    #+#             */
/*   Updated: 2024/04/22 13:30:37 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_command *command)
{
	int		i;
	int		nbr;
	char	*var;

	nbr = 0;
	i = 0;
	var = "_=/usr/bin/env";
	if (ft_var_exist(command, var) == 0)
		ft_add_var(command, var);
	while (command->arguments[nbr])
		nbr++;
	printf("nbr = %d\n", nbr);
	if (nbr > 1)
	{
		printf("%s: %s: No such file or directory\n",
			command->arguments[0], command->arguments[1]);
		return (1);
	}
	while (command->shell->mini_env[i])
	{
		if (ft_is_equal(command->shell->mini_env[i]) == 1)
			printf("%s\n", command->shell->mini_env[i]);
		i++;
	}
	return (0);
}
