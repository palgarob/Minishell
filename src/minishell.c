/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/20 20:12:09 by pepaloma         ###   ########.fr       */
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

void	init_ioflow(t_ioflow *ioflow)
{
	ioflow->input = STDIN_FILENO;
	ioflow->output = STDOUT_FILENO;
	ioflow->ioflow = NULL;
}

int	main(void)
{
	char		*line;
	t_ioflow	ioflow;
	
	//sighandling
	while (1)
	{
		line = readline("$ ");
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			take(line);
			init_ioflow(&ioflow);
			ioflow.command = parse(line);
			if (!ioflow.command)
				return (perror(ERR_PARSE), 1); // Aquí habría que liberar la línea
			while (*ioflow.command)
				ft_printf("*%s*\n", *(ioflow.command++));
		}
	}
	return (0);
}
