/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:57:12 by incalero          #+#    #+#             */
/*   Updated: 2024/04/10 11:10:15 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_echo(t_shell *shell)
{
	int i;
	
	i = 1;
	if (ft_strncmp(shell->first_command.arguments[1], "-n", 2) == 0)
			i++;
	while (shell->first_command.arguments[i])
	{
		ft_print_str(shell->first_command.arguments[i]);
		if (shell->first_command.arguments[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp(shell->first_command.arguments[1], "-n", 2))
		printf("\n");
	return (0);
}

int ft_env(t_shell *shell)
{
	int i;
	i = 0;
	
	while(shell->mini_env[i])
	{
		if (ft_is_equal(shell->mini_env[i]) == 0)
			i++;
		else
			printf("%s\n", shell->mini_env[i]);
		i++;
	}
	return (0);
}

int ft_exit(t_shell *shell)
{
	printf("exit\n");
	//system("leaks minishell");
	ft_free_array(shell->mini_env);
	exit(42);
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

