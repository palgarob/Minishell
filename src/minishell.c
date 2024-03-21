/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 15:18:07 by pepaloma         ###   ########.fr       */
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

int	redirect_io(t_ioflow *ioflow, char **args)
{
	if (**args == '>')
	{
		ioflow->output = open((*args) + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ioflow->output < 0)
			return (perror((*args) + 1), 1);
		ioflow->close_out = true;
	}
	else if (**args == '<')
	{
		ioflow->input = open((*args) + 1, O_RDONLY);
		if (ioflow->input < 0)
			return (perror((*args) + 1), 1);
		ioflow->close_out = true;
	}
}

int	init_ioflow(t_ioflow *ioflow, char **args)
{
	ioflow->input = STDIN_FILENO;
	ioflow->output = STDOUT_FILENO;
	ioflow->ioflow = NULL;
	ioflow->command = NULL;
	ioflow->close_in = false;
	ioflow->close_out = false;
	ioflow->close_pipe = false;
	while (*args)
	{
		if (!is_metachar(**args))
			if (access_values(args) || trim_quotes(args))
				ioflow->command = ft_splitadd(*args, &ioflow->command);
		else if (**args == '>' || **args == '<')
		{
			if (redirect_io(ioflow, args))
				return (1);
			args++;
		}
		/* else if (**args == '|')
			if (pipe(ioflow->pipe_end) < 0)
				return (perror(0), 1);
			ioflow->close_pipe = true */
		args++;
	}
	return (0);
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
				if (init_ioflow(&ioflow, args))
					enter(ioflow);
			}
		}
	}
	return (0);
}
