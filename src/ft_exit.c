/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/15 10:43:42 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command *command)
{
	//exit tiene como argumento el número que devuelve el programa
	// hay que llamar a clear_history
	// error 128 invalid argument to exit
	printf("exit\n");
	//system("leaks minishell");
	ft_splitfree(command->shell->mini_env);
	exit(42);
	return (0);
}
