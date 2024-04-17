/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:15:43 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/17 15:43:02 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	output(t_command *command, char **split_line)
{
	if (expand_parameters(split_line + 1, false,
			command->shell->mini_env, command->shell->les))
		return (1);
	if (command->close_out)
		close(command->close_out);
	if (*(*split_line + 1) == '>')
		command->output = open(*(split_line + 1),
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		command->output = open(*(split_line + 1),
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (command->output < 0)
		return (perror(*(split_line + 1)), 1);
	command->close_out = true;
	return (0);
}

int	redirect_io(t_command *command, char **split_line)
{
	if (**split_line == '>')
	{
		if (output(command, split_line))
			return (1);
	}
	else
	{
		close_input_fd(*command);
		if (*(*split_line + 1) == '<')
		{
			if (here_doc(command, split_line))
				return (1);
		}
		else
		{
			if (expand_parameters(split_line + 1, false,
					command->shell->mini_env, command->shell->les))
				return (1);
			command->input = open(*(split_line + 1), O_RDONLY);
			if (command->input < 0)
				return (perror(*(split_line + 1)), 1);
			command->close_in = true;
		}
	}
	return (0);
}
