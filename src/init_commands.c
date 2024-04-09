/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:38:48 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/09 18:57:36 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipes(t_command *command, char **split_line)
{
	while (*split_line)
	{
		if (**split_line == '|')
		{
			command->piped_command = (t_command *)malloc(sizeof(t_command));
			if (!command->piped_command)
				return (perror(0), 1);
			if (pipe(command->piped_command->pipe_end) < 0)
				return (perror(0), 1);
			command->piped_command->shell = command->shell;
			command = command->piped_command;
			command->close_pipe = true;
			command->piped_command = NULL;
			command->arguments = NULL;
			command->close_in = false;
			command->close_out = false;
		}
		split_line++;
	}
	return (0);
}

static int	init_arguments(t_command *command, char **split_line)
{
	while (*split_line)
	{
		if (**split_line == '>' || **split_line == '<') // si metemos dos redirecciones, tendrá que cerrar las anteriores?
		{
			if (redirect_io(command, split_line))
				return (1);
			split_line++;
		}
		else if (!is_metachar(**split_line))
		{
			if (expand_parameters(split_line, false, command->shell->mini_env, command->shell->les))
				return (1);
			ft_splitadd(*split_line, &command->arguments);
		}
		else if (**split_line == '|')
			command = command->piped_command;
		split_line++;
	}
	return (0);
}

int	init_commands(t_shell *shell, char **split_line)
{
	shell->first_command.piped_command = NULL;
	shell->first_command.close_pipe = false;
	shell->first_command.arguments = NULL;
	shell->first_command.close_in = false;
	shell->first_command.close_out = false;
	shell->first_command.shell = shell;
	if (init_pipes(&shell->first_command, split_line))
		return (1);
	if (init_arguments(&shell->first_command, split_line))
		return (1);
	return (0);
}
