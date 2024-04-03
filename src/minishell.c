/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/03 21:52:01 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	take(char *line)
{
	if (!line)
		exit(0);
	if (*line)
		add_history(line);
}

static void	enter(t_shell shell)
{
	pid_t		wait_process;

	wait_process = exec_commands(shell.first_command);
	if (wait_process > 0)
	{
		close_pipes(shell.first_command);
		waitpid(wait_process, NULL, 0);
	}
}

void	init_shell(t_shell *shell, char **environment)
{
	shell->mini_env = ft_splitdup(environment);
	if (!shell->mini_env)
	{
		perror(NULL);
		exit(1);
	}
	shell->shell_variables = NULL;
	shell->return_val = 0;
	shell->rm_here_doc = false;
}

int	main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **envp)
{
	/* Hay casos en los que probablemente deberemos usar printf antes que ft_printf. Revisar todo para ver en qué casos tenemos que cambiar eso. */
	char		*line;
	char		**split_line;
	t_shell		shell;

	init_shell(&shell, envp);
	while (1)
	{
		line = readline("$ ");
		take(line);
		if (*line) // Aquí quizás se podría poner el control de la señal
		{
			split_line = parse_line(line); // mirar que hacer si le pasamos espacios o tabs vacíos
			if (split_line)
			{
				if (!init_commands(&shell.first_command, split_line))
					enter(shell);
				ft_splitfree(split_line);
				clear_commands(shell.first_command);
				if (shell.rm_here_doc)
					unlink("here_doc");
			}
		} // recuerda manejar pipes con comandos vacíos y esas movidas
	}
	return (0);
}
