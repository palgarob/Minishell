/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:31:42 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/09 18:31:18 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_metachar(char c)
{
	if (
		c == '|' || c == '<' || c == '>'
	)
		return (true);
	return (false);
}

char	*ft_getenv(char *var_name, char **mini_env)
{
	//free memory
	char	*value;

	value = NULL;
	while (*mini_env)
	{
		if (ft_strncmp(*mini_env, var_name, ft_strlen(var_name) + 1) == 61)
		{
			value = *mini_env + ft_strlen(var_name) + 1;
			break;
		}
		mini_env++;
	}
	if (!value)
	{
		value = (char *)malloc(sizeof(char));
		if (!value)
			return (perror(0), NULL);
		*value = 0;
		return (value);
	}
	value = ft_strdup(value);
	if (!value)
		return (perror(0), NULL);
	return (value);
}

int	trim_quotes(char **split_line)
{
	int		j;
	int		quote;
	int		n;

	j = -1;
	n = 0;
	while ((*split_line)[++j])
	{
		if ((*split_line)[j] == '"' || (*split_line)[j] == '\'')
		{
			n++;
			quote = (*split_line)[j];
			if (ft_strins(split_line, j, j + 1, ""))
				return (-1);
			while ((*split_line)[j] != quote)
				j++;
			if (ft_strins(split_line, j, j + 1, ""))
				return (-1);
		}
	}
	return (n);
}

/* This function returns:
	-> 0 if there is a path
	-> 1 if there is no path
	-> -1 if there was an error */
static int	get_path(char **mini_env, char ***path_ptr)
{
	char	*path;

	path = ft_getenv("PATH", mini_env);
	if (!path)
		return (-1);
	if (!*path)
	{
		free(path);
		path = ft_getenv("PWD", mini_env);
		if (!path)
			return (-1);
		if (!*path)
			return (free(path), perror("environment variable PWD missing"), -1);
		*path_ptr = ft_split(path, ':');
		free(path);
		if (!*path_ptr)
			return (-1);
		return (1);
	}
	*path_ptr = ft_split(path, ':');
	free(path);
	if (!*path_ptr)
		return (-1);
	return (0);
}

char	*get_cmd_path(char *cmd_name, char **mini_env)
{
	//memory leaks
	char	*cmd_path;
	char	**path;
	int		i;
	int		no_path;

	no_path = get_path(mini_env, &path);
	if (no_path < 0)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin_gnl(cmd_path, cmd_name);
		if (!access(cmd_path, F_OK))
			break ;
		if (no_path)
			return (perror(cmd_name), free(cmd_path), ft_splitfree(path), NULL);
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_splitfree(path);
	if (cmd_path)
		return (cmd_path);
	return (write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name)), write(STDERR_FILENO, ": command not found\n", 20), NULL);
}
