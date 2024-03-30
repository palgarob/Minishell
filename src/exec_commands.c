/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 01:56:23 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	checc(int prueba)
{
	if (WIFSIGNALED(prueba))
		ft_printf("WIFSIGNALED\n");
	ft_printf("%d\n", WTERMSIG(prueba));
	
}

void	exec_commands(t_command command)
{
	pid_t	pid;
	char	*cmd_path;
	int		prueba;
	
	cmd_path = get_cmd_path(command.path_var, *command.arguments);
	pid = fork();
	if (pid < 0)
	{
		perror(0);
		return ;
	}
	if (!pid)
	{
		if (command.command)
		{
			if (dup2(command.command->pipe_end[1], STDOUT_FILENO) < 0)
			{
				perror(0);
				return ;
			}
			close_pipe(*command.command);
		}
		if (command.close_pipe)
		{
			if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
			{
				perror(0);
				return ;
			}
			close_pipe(command);
		}
		if (command.close_in)
		{
			if (dup2(command.input, STDIN_FILENO) < 0)
			{
				perror(0);
				return ;
			}
		}
		if (command.close_out)
		{
			if (dup2(command.output, STDOUT_FILENO) < 0)
			{
				perror(0);
				return ;
			}
		}
		execve(cmd_path, command.arguments, environ);
	}
	waitpid(pid, &prueba, WNOHANG);
	if (!command.command)
	{usleep(1000);
	checc(prueba);}
	if (command.command)
		exec_commands(*command.command);
	free(cmd_path);
}
