/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/04 13:37:22 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static int	pipes(t_command command)
{
	if (command.piped_command)
		if (dup2(command.piped_command->pipe_end[1], STDOUT_FILENO) < 0)
			return (perror(0), -1);
	if (command.close_pipe)
		if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
			return (perror(0), -1);
	close_pipes(command.shell->first_command);
	return (0);
}

pid_t	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;
	char	**path_var;

	path_var = get_path_var(command.shell->mini_env);
	if (!path_var)
		return (-1);
	cmd_path = get_cmd_path(path_var, *command.arguments);
	free(path_var);
	pid = fork();
	if (pid < 0)
		return (perror(0), -1);
	if (!pid)
	{
		if (command.piped_command || command.close_pipe)
			if (pipes(command))
				return (-1);
		if (command.close_in)
			if (dup2(command.input, STDIN_FILENO) < 0)
				return (perror(0), -1);
		if (command.close_out)
			if (dup2(command.output, STDOUT_FILENO) < 0)
				return (perror(0), -1);
		command.shell->return_val = execve(cmd_path, command.arguments, command.shell->mini_env);
		ft_printf("%d\n");
	}
	free(cmd_path);
	if (command.piped_command)
		return (exec_commands(*command.piped_command));
	return (pid);
}
