/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:57:12 by incalero          #+#    #+#             */
/*   Updated: 2024/04/04 16:29:24 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_echo(t_command command)
{
	int i;
	
	i = 1;
	if (ft_strncmp(command.arguments[1], "-n", 2) == 0)
			i++;
	while (command.arguments[i])
	{
		ft_print_str(command.arguments[i]);
		if (command.arguments[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(command.arguments[1], "-n", 2))
		printf("\n");
	return (0);
}

int ft_env(t_command command)
{
	int i;

	i = 0;
	ft_printf("POINTER env12 %p \n", command.env_mini);
	
	while(command.env_mini[i])
	{
		printf("%s\n", command.env_mini[i]);
		i++;
	}	
	ft_printf("POINTER env2 %p \n", command.env_mini);
	return (0);
}

int ft_exit(t_command command)
{
	command.arguments[0] = NULL;

	
	printf("ha entrado en exit\n");
	return (0);
}

int ft_pwd(void)
{
	char cwd[1024];
	
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        ft_print_str(cwd);
		printf("\n");
	}
	else
		return (perror("Error al obtener el directorio actual"), 1);
	return (0);
}

