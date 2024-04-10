/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/10 10:00:07 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **s)
{
	int i;

	i = 0;
	while(s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_get_env(char **env)
{
	int		i;
	char	**envcp;

	i = 0;
	while (env[i])
		i++;
	envcp = malloc(sizeof(char *) * (i + 1));
	envcp[i] = NULL;
	i = 0;
	while (env[i])
	{
		envcp[i] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	return (envcp);
}

static void	enter(t_shell *shell, char **split_line)
{
	pid_t		wait_process;

	if (!init_commands(shell, split_line))
	{
		wait_process = exec_commands(shell->first_command);
		if (wait_process > 0)
		{
			close_pipes(shell->first_command);
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

static void	prompt(t_shell *shell)
{
	char		*line;
	char		**split_line;
	
	line = readline("$ ");
	if (!line)
		exit(0);
	if (*line)
	{
		add_history(line);
		split_line = parse_line(line);
		if (split_line)
		{
			if (ft_is_command(&shell) == 1)
						ft_case (&shell);
			else
				enter(shell, split_line);
		}
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
