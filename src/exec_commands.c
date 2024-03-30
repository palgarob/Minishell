/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 14:22:05 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

pid_t	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;
	
	cmd_path = get_cmd_path(command.path_var, *command.arguments);
	pid = fork();
	if (pid < 0)
		return (perror(0), -1);
	if (!pid)
	{
		if (command.command)
		{
			if (dup2(command.command->pipe_end[1], STDOUT_FILENO) < 0)
			{
				return (perror(0), -1);
			}
		}
		if (command.close_pipe)
		{
			if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
			{
				return (perror(0), -1);
			}
		}
		if (command.command || command.close_pipe)
			close_pipes(*command.first_command);
		if (command.close_in)
		{
			if (dup2(command.input, STDIN_FILENO) < 0)
				return (perror(0), -1);
		}
		if (command.close_out)
		{
			if (dup2(command.output, STDOUT_FILENO) < 0)
				return (perror(0), -1);
		}
		execve(cmd_path, command.arguments, environ);
	}
	free(cmd_path);
	if (command.command)
		return(exec_commands(*command.command));
	return (pid);
}
