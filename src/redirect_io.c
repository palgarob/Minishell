/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:15:43 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/02 18:42:18 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc(t_command *command, char **split_line)
{
	char	*line;
	char	*content;
	bool	quoted;

	quoted = trim_quotes(split_line);
	command->input = open("here_doc", O_RDWR);
	if (command->input < 0)
		return (perror("here_doc"), 1);
	command->rm_here_doc = true;
	while (1)
	{
		line = readline("> ");
		
	}
}

static int	output(t_command *command, char **split_line)
{
	if (expand_parameters(split_line + 1, false))
		return (1);
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
		if (output(command, split_line))
			return (1);
	else
	{
		if (*(*split_line + 1) == '<')
			if (here_doc(command, split_line))
				return (1);
		else
		{
			if (expand_parameters(split_line + 1, false))
				return (1);
			command->input = open(*(split_line + 1), O_RDONLY);
			if (command->input < 0)
				return (perror(*(split_line + 1)), 1);
		}
		command->close_in = true;
	}
	return (0);
}
