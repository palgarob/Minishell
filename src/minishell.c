/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/16 15:13:52 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interactive_m(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	default_m(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		kill(wp, SIGINT);
	}
	if (signum == SIGQUIT)
	{
		printf("Quit: 3\n");
		kill(wp, SIGQUIT);
	}
}

static void	enter(t_shell *shell, char **split_line)
{
	if (!init_commands(shell, split_line))
		exec_commands(shell->first_command);
	clear_commands(shell->first_command);
}

static void	init_shell(t_shell *shell, char **environment)
{
	shell->mini_env = ft_splitdup(environment);
	//eliminar y modificar variables de entorno que haya que modificar
	if (!shell->mini_env)
	{
		perror(NULL);
		exit(1);
	}
	shell->les = 0;
	shell->rm_here_doc = false;
}

int	main(__attribute__((unused)) int argc,
		__attribute__((unused)) char **argv,
		char **envp)
{
	t_shell		shell;
	char		*line;
	char		**split_line;

	init_shell(&shell, envp);
	while (1)
	{
		signal(SIGINT, interactive_m);
		signal(SIGQUIT, interactive_m);
		line = readline("$ ");
		signal(SIGINT, default_m);
		signal(SIGQUIT, default_m);
		if (!line)
			break ; //rl_clear_history y tiene que llamar a la función ft_exi
		if (*line)
		{
			add_history(line);
			split_line = parse_line(line);
			if (split_line)
				enter(&shell, split_line);
			ft_splitfree(split_line);
		}
	}
	ft_exit(shell.first_command);
	return (0);
}
