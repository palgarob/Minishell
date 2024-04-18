/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/18 21:20:34 by pepaloma         ###   ########.fr       */
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

static void	default_m(int signum)
{
	if (signum == SIGINT)
		ft_printf("\n");
	if (signum == SIGQUIT)
		printf("Quit: 3\n");
}

static void	enter(t_shell *shell, char **split_line)
{
	signal(SIGINT, default_m);
	if (!init_commands(shell, split_line))
	{
		signal(SIGQUIT, default_m);
		exec_commands(shell->first_command);
	}
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
	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdin_fd == -1 || shell->stdout_fd == -1)
	{
		perror(NULL);
		ft_splitfree(shell->mini_env);
		exit(1);
	}
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
		if (!line)
		{
			printf("\033[A");
			printf("$ ");
			break ;
		}
		if (*line)
		{
			add_history(line);
			split_line = parse_line(line);
			if (split_line)
				enter(&shell, split_line);
			ft_splitfree(split_line);
		}
	}
	ft_exit(shell);
	return (0);
}
