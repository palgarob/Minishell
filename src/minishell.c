/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 08:59:46 by pepaloma         ###   ########.fr       */
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
					exec_commands(&command);
				ft_splitfree(split_line);
				clear_commands(&command); // piensa en el tema de cómo liberar split_line, cómo está guardado, etc.
			}
		} // recuerda manejar pipes con comandos vacíos y esas movidas
	}
	return (0);
}
