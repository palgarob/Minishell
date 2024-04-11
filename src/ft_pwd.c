/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:19:04 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/11 15:40:17 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_print_str(cwd);
		printf("\n");
	}
	else
	{
		perror("error al obtener el directorio actual"); // getcwd pone errno en algún valor?
		exit(1);
	}
	exit(0);
}
