/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:22:49 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/29 09:34:11 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe(t_command command)
{
	close(command.pipe_end[0]);
	close(command.pipe_end[1]);
}

void	close_pipes(t_command command)
{
	if (command.close_pipe)
		close_pipe(command);
	if (command.piped_command)
		close_pipes(*command.piped_command);
}

void	close_fd(t_command command, int io)
{
	if (io)
	{
		if (command.close_out)
			close(command.output);
	}
	else
	{
		if (command.close_in)
			close(command.input);
	}
}

void	clear_commands(t_command command)
{
	t_command	*aux;

	if (command.shell->rm_here_doc)
		unlink("here_doc");
	if (command.close_in)
		close(command.input);
	if (command.close_out)
		close(command.output);
	if (command.arguments)
		free(command.arguments);
	while (command.piped_command)
	{
		if (command.piped_command->close_in)
			close(command.piped_command->input);
		if (command.piped_command->close_out)
			close(command.piped_command->output);
		if (command.piped_command->arguments)
			free(command.piped_command->arguments);
		aux = command.piped_command;
		command = *command.piped_command;
		if (aux)
			free(aux);
	}
}

void	perror_exit(void)
{
	perror(NULL);
	exit(1);
}
