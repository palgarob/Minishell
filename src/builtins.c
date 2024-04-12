/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:28:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/12 15:03:32 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_command command)
{
	if (ft_strncmp(*command.arguments, "echo", 5) == 0)
		return (ft_echo(command));
	else if (ft_strncmp(*command.arguments, "cd", 3) == 0)
		return (ft_cd(command));
	else if (ft_strncmp(*command.arguments, "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(*command.arguments, "export", 7) == 0)
		return (ft_export(command));
	else if (ft_strncmp(*command.arguments, "unset", 6) == 0)
		return (ft_unset(command));
	else if (ft_strncmp(*command.arguments, "env", 4) == 0)
		return (ft_env(command));
	else if (ft_strncmp(*command.arguments, "exit", 5) == 0)
		return (ft_exit(command));
	else
		return (1);
}
