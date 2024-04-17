/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/17 13:22:01 by pepaloma         ###   ########.fr       */
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
	exit(42);
	return (0);
}
