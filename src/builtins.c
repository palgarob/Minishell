/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:28:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/17 11:46:21 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_builtin(t_command *command)
{
	if (ft_strncmp(command->arguments[0], "echo", 5) == 0)
		return (ft_echo(command));
	if (ft_strncmp(command->arguments[0], "cd", 3) == 0)
		return (ft_cd(command));
	if (ft_strncmp(command->arguments[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(command->arguments[0], "export", 7) == 0)
		return (ft_export(command));
	if (ft_strncmp(command->arguments[0], "unset", 6) == 0)
		return (ft_unset(command));
	if (ft_strncmp(command->arguments[0], "env", 4) == 0)
		return (ft_env(command));
	if (ft_strncmp(command->arguments[0], "exit", 5) == 0)
		return (ft_exit(command));
	return (1);
}
