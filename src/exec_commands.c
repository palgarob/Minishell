/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:52:16 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/18 15:35:37 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	path_exists(char **mini_env)
{
	while (*mini_env)
	{
		if (ft_strncmp(*mini_env, "PATH", 5) == 61)
			return (true);
		mini_env++;
	}
	return (false);
}

static void	redirections(t_command command)
{
	if (command.piped_command)
		if (dup2(command.piped_command->pipe_end[1], STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit(1);
		}
	if (command.close_pipe)
		if (dup2(command.pipe_end[0], STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit(1);
		}
	close_pipes(command.shell->first_command);
	if (command.close_in)
		if (dup2(command.input, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit(1);
		}
	if (command.close_out)
		if (dup2(command.output, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit(1);
		} 
}

void	exec_prog(t_command command)
{
	char	*cmd_path;
	
	if (ft_strchr(*command.arguments, '/') || !path_exists(command.shell->mini_env))
	{
		if (access(*command.arguments, F_OK))
			return (perror(*command.arguments), exit(127));
		cmd_path = *command.arguments;
	}
	else
		cmd_path = get_cmd_path(*command.arguments, command.shell->mini_env);
	if (!cmd_path)
		exit(1);
	if (execve(cmd_path, command.arguments, command.shell->mini_env))
	{
		perror(cmd_path);
		if (errno == 13)
			exit(126);
		/* else
			exit(1); */
	}
}

static pid_t	exec_pipes(t_command command)
{
	pid_t	pid;

	if (!command.piped_command && is_builtin(*command.arguments))
		return (exec_builtin(&command));
	pid = fork();
	if (pid < 0)
		return (perror(0), -1);
	if (!pid)
	{
		redirections(command);
		if (is_builtin(*command.arguments))
			exit(exec_builtin(&command));
		exec_prog(command);
	}
	if (command.piped_command)
		return (exec_pipes(*command.piped_command));
	return (pid);
}

/* static void	redirections_builts(t_command *command)
{
	printf("input = %d\n", command->input);
	if (expand_parameters(split_line + 1, false, command->shell->mini_env, command->shell->les))
		return (1);
	command->input = open(*(split_line + 1), O_RDONLY);
	if (command->input < 0)
		return (perror(*(split_line + 1)), 1);
	command->close_in = true;
} */

void	exec_commands(t_command command)
{
	pid_t		wait_process;

	if (command.piped_command || !is_builtin(*command.arguments))
	{
		wait_process = exec_pipes(command);
		close_pipes(command);
		if (wait_process > 0)
		{
			wp = wait_process;
			waitpid(wait_process, &command.shell->les, 0);
			if (WIFEXITED(command.shell->les))
				command.shell->les = WEXITSTATUS(command.shell->les);
			else if (WIFSIGNALED(command.shell->les))
				command.shell->les = WTERMSIG(command.shell->les) + 128;
		}
	}
	else
	{
		if (command.close_in)
		{
			if (dup2(command.input, STDIN_FILENO) < 0)
			{
				perror(NULL);
				exit(1);
			}
			close (command.input);
		}
		if (command.close_out)
		{
			if (dup2(command.output, STDOUT_FILENO) < 0)
			{
				perror(NULL);
				exit(1);
			}
			close (command.output);
		}
		command.shell->les = exec_builtin(&command);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
	}
}  