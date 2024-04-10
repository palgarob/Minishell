/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/10 21:32:17 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **s)
{
	int i;

	i = 0;
	while(s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static void	take(char *line)
{
	if (!line)
		exit(0);
	if (*line)
		add_history(line);
}

static void	enter(t_command command)
{
	pid_t		wait_process;

	wait_process = exec_commands(command);
	if (wait_process > 0)
	{
		close_pipes(command);
		waitpid(wait_process, NULL, 0);
	}
}

char	**ft_get_env(char **env)
{
	int		i;
	char	**envcp;

	i = 0;
	while (env[i])
		i++;
	envcp = malloc(sizeof(char *) * (i + 1));
	envcp[i] = NULL;
	i = 0;
	while (env[i])
	{
		envcp[i] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	return (envcp);
}


int	main(int argc, char *argv[], char **env)
{
	char		*line;
	char		**split_line;
	t_command	command;

	if (argc > 1)
		return (perror("Error de argumentos"), -1);
	argv = NULL;
	if (!env)
		return (perror("Err: env not exit"), -1);
	command.env_mini = ft_get_env(env);
	command.env_mini = ft_dell_var(command, "OLDPWD");
	while (1)
	{
		line = readline("minishell$>");
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			take(line);
			split_line = parse_line(line); // mirar que hacer si le pasamos espacios o tabs vacíos
			if (split_line)
			{
				if (!init_commands(&command, split_line))
				{
					if (ft_is_command(&command) == 1)
						ft_case (&command);
					else
					{
						ft_command_no_found(&command);
						enter(command);
					}
				}
				ft_splitfree(split_line);
				clear_commands(command);
			}
		} // recuerda manejar pipes con comandos vacíos y esas movidas
	} 
}
