/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:38:48 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/28 20:08:48 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_io(t_command *command, char **split_line)
{
	if (**split_line == '>')
	{
		command->output = open(*(split_line + 1), O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (command->output < 0)
			return (perror(*(split_line + 1)), 1);
		command->close_out = true;
	}
	else if (**split_line == '<')
	{
		command->input = open(*(split_line + 1), O_RDONLY);
		if (command->input < 0)
			return (perror(*(split_line + 1)), 1);
		command->close_in = true;
	}
	return (0);
}

int	init_pipes(t_command *command, char **split_line)
{
	while (*split_line)
	{
		if (**split_line == '|')
		{
			command->command = (t_command *)malloc(sizeof(t_command));
			if (!command->command)
				return (perror(0), 1);
			if (pipe(command->command->pipe_end) < 0)
				return (perror(0), 1);
			command = command->command;
			command->close_pipe = true;
			command->command = NULL;
			command->arguments = NULL;
			command->input = STDIN_FILENO;
			command->close_in = false;
			command->output = STDOUT_FILENO;
			command->close_out = false;
			command->path_var = get_path_var();
		}
		split_line++;
	}
	return (0);
}

int	init_command(t_command *command, char **split_line)
{
	while (*split_line)
	{
		if (!is_metachar(**split_line))
		{
			if (access_values(split_line) || trim_quotes(split_line))
				return (1);
			ft_splitadd(*split_line, &command->arguments);
		}
		else if (**split_line == '>' || **split_line == '<') // si metemos dos redirecciones, tendrá que cerrar las anteriores?
		{
			if (redirect_io(command, split_line))
				return (1);
			split_line++;
		}
		else if (**split_line == '|')
			command = command->command;
		split_line++;
	}
	return (0);
}

int	init_commands(t_command *command, char **split_line)
{
	command->command = NULL;
	command->close_pipe = false;
	command->arguments = NULL;
	command->input = STDIN_FILENO;
	command->close_in = false;
	command->output = STDOUT_FILENO;
	command->close_out = false;
	command->path_var = get_path_var();
	init_pipes(command, split_line);
	init_command(command, split_line);
	return (0);
}
