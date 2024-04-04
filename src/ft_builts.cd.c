/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts.cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:00 by incalero          #+#    #+#             */
/*   Updated: 2024/04/04 12:35:20 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_directory_cmp(void)
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

int ft_change_directory(const char *directory)
{
	ft_directory_cmp();
	printf("directory = %s\n", directory);
	if (directory == NULL || directory[0] == '~') // Si no se proporciona ningún argumento o es la variable de entorno $USER, cambia al directorio de inicio del usuario
	{
        if (chdir(getenv("HOME")) != 0) 
		{
            perror("Error al cambiar al directorio de inicio");
            return (-1);
		}
	}
	
	else if (chdir(directory) != 0)
	{
		write (1, "cd: ", 4);
        return (perror((char *)directory), -1);
	}
	ft_directory_cmp();
	return (0);
}

int ft_cd (t_command command)
{
	if (!command.arguments[1])
		ft_change_directory(NULL);
	ft_change_directory(command.arguments[1]);
	return (0);
}

int ft_case(t_command command)
{
	if (ft_strncmp(command.arguments[0], "echo\0", 5) == 0)
		return(ft_echo (command), 1);
	else if (ft_strncmp(command.arguments[0], "cd", 2) == 0)
		return(ft_cd (command), 1);
	else if (ft_strncmp(command.arguments[0], "pwd", 3) == 0)
		return (ft_pwd (), 1);
	else if (ft_strncmp(command.arguments[0], "export", 6) == 0)
		return (ft_export (command), 1);
	else if (ft_strncmp(command.arguments[0], "unset", 5) == 0)
		return (ft_unset (command), 1);
	else if (ft_strncmp(command.arguments[0], "env", 3) == 0)
		return (ft_env (command), 1);
	else if (ft_strncmp(command.arguments[0], "exit", 4) == 0)
		return (ft_exit (command), 1);
	return (0);
}

