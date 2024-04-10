/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts.cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:02:00 by incalero          #+#    #+#             */
/*   Updated: 2024/04/10 10:17:46 by incalero         ###   ########.fr       */
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
	//ft_directory_cmp();
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
	//ft_directory_cmp();
	return (0);
}

int ft_cd (t_shell *shell)
{
	if (!shell->first_command.arguments[1])
		ft_change_directory(NULL);
	ft_change_directory(shell->first_command.arguments[1]);
	return (0);
}

void ft_case(t_shell *shell)
{
	if (ft_strncmp(shell->first_command.arguments[0], "echo\0", 5) == 0)
		ft_echo (shell);
	else if (ft_strncmp(shell->first_command.arguments[0], "cd", 2) == 0)
		ft_cd (shell);
	else if (ft_strncmp(shell->first_command.arguments[0], "pwd", 3) == 0)
		ft_pwd ();
	else if (ft_strncmp(shell->first_command.arguments[0], "export", 6) == 0)
		ft_export (shell);
	else if (ft_strncmp(shell->first_command.arguments[0], "unset", 5) == 0)
		ft_unset (shell);
	else if (ft_strncmp(shell->first_command.arguments[0], "env", 3) == 0)
		ft_env (shell);
	else if (ft_strncmp(shell->first_command.arguments[0], "exit", 4) == 0)
		ft_exit (shell);
}

