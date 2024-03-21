/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 03:36:11 by pepaloma         ###   ########.fr       */
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

void	init_ioflow(t_ioflow *ioflow, char **args)
{
	ioflow->input = STDIN_FILENO;
	ioflow->output = STDOUT_FILENO;
	ioflow->ioflow = NULL;
	ioflow->command = NULL;
	while (*args)
	{
		if (!is_metachar(**args))
			if (access_values(args))
	}
}

void	enter(t_ioflow ioflow)
{
	pid_t	pid;

	
}

int	main(void)
{
	char		*line;
	char		*args;
	t_ioflow	ioflow;
	
	while (1)
	{
		line = readline("$>");
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			take(line);
			args = parse(line);
			if (args)
			{
				init_ioflow(&ioflow, args);
				enter(ioflow);
			}
		}
	}
	return (0);
}
