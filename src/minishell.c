/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/01 21:03:49 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(void)
{
	/* Hay casos en los que probablemente deberemos usar printf antes que ft_printf. Revisar todo para ver en qué casos tenemos que cambiar eso. */
	char		*line;
	char		**split_line;
	t_command	command;

	while (1)
	{
		line = readline("$ ");
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			take(line);
			split_line = parse_line(line); // mirar que hacer si le pasamos espacios o tabs vacíos
			if (split_line)
			{
				if (!init_commands(&command, split_line))
					enter(command);
				ft_splitfree(split_line);
				clear_commands(command);
			}
		} // recuerda manejar pipes con comandos vacíos y esas movidas
	}
	return (0);
}
