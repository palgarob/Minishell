/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:15:43 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/16 12:16:08 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_rl(t_command *command, char **split_line, int quoted,
		char **content_ptr)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (1);
	if (!ft_strncmp(*(split_line + 1), line, ft_strlen(line) + 1))
		return (1);
	if (!quoted)
		if (expand_parameters(&line, true, command->shell->mini_env,
				command->shell->les))
			return (-1);
	*content_ptr = ft_strjoin_gnl(*content_ptr, line); //memory
	*content_ptr = ft_strjoin_gnl(*content_ptr, "\n");
	return (0);
}

static int	open_here_doc(t_command *command, char **split_line)
{
	int	quoted;

	quoted = trim_quotes(split_line + 1);
	if (quoted < 0)
		return (-1);
	command->input = open("here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (command->input < 0)
		return (perror("here_doc"), -1);
	command->close_in = true;
	command->shell->rm_here_doc = true;
	return (quoted);
}

static int	here_doc(t_command *command, char **split_line)
{
	int		quoted;
	char	*content;
	int		control;

	quoted = open_here_doc(command, split_line);
	if (quoted == -1)
		if (quoted < 0)
			return (-1);
	content = NULL;
	while (1)
	{
		control = here_rl(command, split_line, quoted, &content);
		if (control == -1)
			return (1);
		if (control)
			break ;
	}
	if (content)
		write(command->input, content, ft_strlen(content));
	close(command->input);
	command->input = open("here_doc", O_RDONLY);
	return (0);
}

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
