/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/22 11:06:34 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

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
	return (0);
}

int	init_ioflow(t_ioflow *ioflow, char **args)
{
	ioflow->ioflow = NULL;
	ioflow->input = STDIN_FILENO;
	ioflow->output = STDOUT_FILENO;
	ioflow->command = NULL;
	ioflow->close_in = false;
	ioflow->close_out = false;
	ioflow->close_pipe = false;
	ioflow->path_var = get_path_var();
	while (*args)
	{
		if (!is_metachar(**args))
		{
			if (access_values(args) || trim_quotes(args))
				ft_splitadd(*args, &ioflow->command);
		}
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

int	enter(t_ioflow ioflow)
{
	pid_t	pid;
	char	*cmd_path;
	
	cmd_path = get_cmd_path(ioflow.path_var, *ioflow.command);
	pid = fork();
	/* if (pid < 0)
		return (clear_ioflow(ioflow), 1); */
	if (!pid)
	{
		if (dup2(ioflow.input, STDIN_FILENO) || dup2(ioflow.output, STDOUT_FILENO))
			return (perror(0), /* clear_ioflow(ioflow), */1);
		execve(cmd_path, ioflow.command, environ);
	}
	waitpid(pid, NULL, WNOHANG);
	return (0);
}

int	main(void)
{
	char		*line;
	char		**args;
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
