/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:28:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/12 11:32:46 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(t_command command)
{
	if (ft_strncmp(*command.arguments, "echo", 5) == 0)
		ft_echo(command);
	else if (ft_strncmp(*command.arguments, "cd", 3) == 0)
		ft_cd(command);
	else if (ft_strncmp(*command.arguments, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(*command.arguments, "export", 7) == 0)
		ft_export(command);
	else if (ft_strncmp(*command.arguments, "unset", 6) == 0)
		ft_unset(command);
	else if (ft_strncmp(*command.arguments, "env", 4) == 0)
		ft_env(command); 
	else if (ft_strncmp(*command.arguments, "exit", 5) == 0)
		ft_exit(command);
}
