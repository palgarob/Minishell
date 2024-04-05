/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/05 13:25:10 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

int ft_is_command (t_command *command)
{
	if (ft_strncmp(command->arguments[0], "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(command->arguments[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(command->arguments[0], "pwd", 3) == 0) 
		return (1);
	else if (ft_strncmp(command->arguments[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(command->arguments[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(command->arguments[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(command->arguments[0], "exit", 4) == 0)
		return (1);
	else
		return (0);
}

static int	pipes(t_command command)
{
	if (command.command)
		if (dup2(command.command->pipe_end[1], STDOUT_FILENO) < 0)
			return (perror(0), -1);
	if (command.close_pipe)
		if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
			return (perror(0), -1);
	close_pipes(*command.first_command);
	return (0);
}

pid_t	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = get_cmd_path(command.path_var, *command.arguments);
	{
		pid = fork();
		if (pid < 0)
			return (perror(0), -1);
		if (!pid)
		{
			if (command.command || command.close_pipe)
				if (pipes(command))
					return (-1);
			if (command.close_in)
				if (dup2(command.input, STDIN_FILENO) < 0)
					return (perror(0), -1);
			if (command.close_out)
				if (dup2(command.output, STDOUT_FILENO) < 0)
					return (perror(0), -1);
			execve(cmd_path, command.arguments, command.env_mini);
		}

	}
	free(cmd_path);
	if (command.command)
		return (exec_commands(*command.command));
	printf ("FFFFFFFFFFFFFF\n");
	return (pid);
}
