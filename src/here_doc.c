/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:41:35 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/18 20:46:04 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_rl(t_command *command, char **split_line, int quoted,
		char **content_ptr)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_printf("\033[A");
		ft_printf("> ");
		return (1);
	}
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
	return (quoted);
}

static int	here_doc1(t_command *command, char **split_line)
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
			return (close(command->input), 1);
		if (control)
			break ;
	}
	if (content)
		write(command->input, content, ft_strlen(content));
	close(command->input);
	return (0);
}

int	here_doc(t_command *command, char **split_line)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror(NULL), 1);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		exit(here_doc1(command, split_line));
	}
	waitpid(pid, &status, 0);
	command->shell->rm_here_doc = true; //comprobar con access
	if (status)
		return (1);
	command->input = open("here_doc", O_RDONLY);
	command->close_in = true;
	return (0);
}
