/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/11 13:25:19 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	perror_exit(char *message)
{
	perror(message);
	exit(1);
}

static void	redirections(t_command command)
{
	if (command.piped_command)
		if (dup2(command.piped_command->pipe_end[1], STDOUT_FILENO) < 0)
			perror_exit(NULL);
	if (command.close_pipe)
		if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
			perror_exit(NULL);
	close_pipes(command.shell->first_command);
	if (command.close_in)
		if (dup2(command.input, STDIN_FILENO) < 0)
			perror_exit(NULL);
	if (command.close_out)
		if (dup2(command.output, STDOUT_FILENO) < 0)
			perror_exit(NULL);
}

pid_t	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid < 0)
		return (perror(0), -1);
	if (!pid)
	{
		redirections(command);
		cmd_path = get_cmd_path(*command.arguments, command.shell->mini_env);
		if (!cmd_path)
			exit(1);
		execve(cmd_path, command.arguments, command.shell->mini_env);
		perror_exit(cmd_path);
	}
	if (command.piped_command)
		return (exec_commands(*command.piped_command));
	return (pid);
}
