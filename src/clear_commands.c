/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:22:49 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 01:27:03 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_command command)
{
	close(command.pipe_end[0]);
	close(command.pipe_end[1]);
}

void	clear_commands(t_command command)
{
	if (command.close_in)
		close(command.input);
	if (command.close_out)
		close(command.output);
	if (command.close_pipe)
		close_pipe(command);
	ft_splitfree(command.path_var);
	if (command.command)
		clear_commands(*command.command);
	// super importante ver como se almacenan los args y los comandos para poder liberarlos correctamente
	// recordar que esta función tiene que ser recursiva para liberar la cadena de pipes
}
