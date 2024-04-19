/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/19 12:47:12 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell shell)
{
	//exit tiene como argumento el número que devuelve el programa
	// hay que llamar a clear_history
	// error 128 invalid argument to exit
	printf("exit\n");
	//system("leaks minishell");
	ft_splitfree(shell.mini_env);
	exit(0);
	return (0);
}
