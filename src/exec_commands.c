/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 00:30:11 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;
	
	cmd_path = get_cmd_path(command.path_var, *command.arguments);
	pid = fork();
	if (pid < 0)
	{
		perror(0);
		return ;
	}
	if (!pid)
	{
		if (dup2(command.input, STDIN_FILENO) < 0 || dup2(command.output, STDOUT_FILENO) < 0)
		{
			perror(0);
			return ;
		}
		if (command.command)
			close_pipe(*command.command);
		if (command.close_pipe)
			close_pipe(command);
		execve(cmd_path, command.arguments, environ);
	}
	wait(NULL);
	if (command.command)
		exec_commands(*command.command);
	free(cmd_path);
}
