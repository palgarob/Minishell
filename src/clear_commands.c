/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:22:49 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/30 15:17:34 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipe(t_command command)
{
	close(command.pipe_end[0]);
	close(command.pipe_end[1]);
}

void	close_pipes(t_command command)
{
	if (command.close_pipe)
		close_pipe(command);
	if (command.command)
		close_pipes(*command.command);
}

void	clear_commands(t_command command)
{
	if (command.close_in)
		close(command.input);
	if (command.close_out)
		close(command.output);
	ft_splitfree(command.path_var);
	if (command.command)
		clear_commands(*command.command);
	// Mirar la forma de liberar los mallocs hechos para cada command
}
