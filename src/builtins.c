/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:28:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/18 21:27:30 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_redirections(t_shell shell)
{
	if (dup2(shell.stdin_fd, STDIN_FILENO) < 0
		|| dup2(shell.stdout_fd, STDOUT_FILENO) < 0)
		return (perror(NULL), 1);
	return (0);
}

bool	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (true);
	return (false);
}

int	exec_builtin(t_command command)
{
	int	status;

	if (ft_strncmp(*command.arguments, "echo", 5) == 0)
		status = ft_echo(command);
	else if (ft_strncmp(*command.arguments, "cd", 3) == 0)
		status = ft_cd(command);
	else if (ft_strncmp(*command.arguments, "pwd", 4) == 0)
		status = ft_pwd();
	else if (ft_strncmp(*command.arguments, "export", 7) == 0)
		status = ft_export(command);
	else if (ft_strncmp(*command.arguments, "unset", 6) == 0)
		status = ft_unset(command);
	else if (ft_strncmp(*command.arguments, "env", 4) == 0)
		status = ft_env(command);
	else if (ft_strncmp(*command.arguments, "exit", 5) == 0)
		status = ft_exit(*command.shell);
	if (restore_redirections(*command.shell))
		return (1);
	return (status);
}
