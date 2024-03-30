/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 14:03:47 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take(char *line)
{
	if (!line)
		exit(0);
	if (*line)
		add_history(line);
}

int	main(void)
{
	char		*line;
	char		**split_line;
	t_command	command;
	pid_t		wait_process;
	
	while (1)
	{
		line = readline("$>");
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			take(line);
			split_line = parse_line(line); // mirar que hacer si le pasamos espacios o tabs vacíos
			if (split_line)
			{
				if (!init_commands(&command, split_line))
				{
					wait_process = exec_commands(command);
					if (wait_process > 0)
					{
						close_pipes(command);
						waitpid(wait_process, NULL, 0);
					}
				}
				ft_splitfree(split_line);
				clear_commands(command); // piensa en el tema de cómo liberar split_line, cómo está guardado, etc.
			}
		} // recuerda manejar pipes con comandos vacíos y esas movidas
	}
	return (0);
}
