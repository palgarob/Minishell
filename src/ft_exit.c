/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/16 15:14:00 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command command)
{
	(void)command;
	//exit tiene como argumento el número que devuelve el programa
	// hay que llamar a clear_history
	// error 128 invalid argument to exit
	printf("exit\n");
	//system("leaks minishell");
	ft_splitfree(command.shell->mini_env);
	exit(42);
	return (0);
}
