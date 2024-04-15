/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:00 by incalero          #+#    #+#             */
/*   Updated: 2024/04/15 13:55:50 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_directory_cmp(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("Directorio actual: %s\n", cwd);
	}
	else
	{
		perror("Error al obtener el directorio actual");
		return (-1);
	}
	return (0);
}

int	ft_change_directory(t_command *commond, const char *directory)
{
	//ft_directory_cmp();
	if (directory == NULL || directory[0] == '~') // Si no se proporciona ningún argumento o es la variable de entorno $USER, cambia al directorio de inicio del usuario
	{
		if (chdir(getenv("HOME")) != 0) 
		{
			perror("Error al cambiar al directorio de inicio");
			return (-1);
		}
		ft_add_var (commond, "OLDPWD");
	}
	else if (chdir(directory) != 0)
	{
		write (1, "cd: ", 4);
		return (perror((char *)directory), -1);
	}
	//ft_directory_cmp();
	return (0);
}

int	ft_cd(t_command *command)
{
	if (!command->arguments[1])
		ft_change_directory(command, NULL);
	ft_change_directory(command, command->arguments[1]);
	return (0);
}
