/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:22:49 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/04 12:47:46 by pepaloma         ###   ########.fr       */
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
	if (command.piped_command)
		close_pipes(*command.piped_command);
}

void	clear_commands(t_command command)
{
	if (command.close_in)
		close(command.input);
	if (command.close_out)
		close(command.output);
	if (command.piped_command)
	{
		clear_commands(*command.piped_command);
		free(command.piped_command);
	}
}
