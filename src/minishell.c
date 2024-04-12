/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/12 14:40:21 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	enter(t_shell *shell, char **split_line)
{
	pid_t		wait_process;

	if (!init_commands(shell, split_line))
	{
		if (builtins(shell->first_command))
		{
			wait_process = exec_commands(shell->first_command);
			close_pipes(shell->first_command);
			if (wait_process > 0)
				waitpid(wait_process, &shell->les, 0);
		}
	}
	ft_splitfree(split_line);
	clear_commands(shell->first_command);
	if (shell->rm_here_doc)
		unlink("here_doc");
}

static void	init_shell(t_shell *shell, char **environment)
{
	shell->mini_env = ft_splitdup(environment);
	//eliminar y modificar variables de entorno que haya que modificar (como el level o el _= ...)
	if (!shell->mini_env)
	{
		perror(NULL);
		exit(1);
	}
	shell->les = 0;
	shell->rm_here_doc = false;
}

void	handler(__attribute__((unused)) int signum)
{
//	No quiero que se imprima  ^C cuando envío la señal
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	prompt(t_shell *shell)
{
	char		*line;
	char		**split_line;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("$ ");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!line)
		exit(0); //rl_clear_history y tiene que llamar a la función ft_exit
	if (*line)
	{
		add_history(line);
		split_line = parse_line(line);
		if (split_line)
			enter(shell, split_line);
	}
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	t_shell		shell;

	init_shell(&shell, envp);
	while (1)
		prompt(&shell);
	return (0);
}
