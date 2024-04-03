/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:31:42 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/03 21:59:27 by pepaloma         ###   ########.fr       */
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
	ft_printf("HOLA\n");
			value = *mini_env + ft_strlen(var_name);
			break;
		}
		mini_env++;
	}
	if (!value)
	{
		value = (char *)malloc(sizeof(char) * 1);
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

char	**get_path_var(char **mini_env)
{
	char	**path_var;
	char	*path;

	path = ft_getenv("PATH", mini_env);
	if (!path)
		return (NULL);
	path_var = ft_split(path, ':');
	if (!path_var)
		return (NULL);
	return (path_var);
}

char	*get_cmd_path(char **path_var_dir, char *cmd_name)
{
	char	*cmd_path;

	while (*path_var_dir)
	{
		cmd_path = (char *)malloc(
				sizeof(char) * (
					ft_strlen(*path_var_dir) + ft_strlen(cmd_name) + 2
					)
				);
		if (!cmd_path)
			return (perror(0), NULL);
		*cmd_path = 0;
		ft_strlcat(
			cmd_path, *path_var_dir, ft_strlen(*path_var_dir) + 1
			);
		ft_strlcat(cmd_path, "/", ft_strlen(cmd_path) + 2);
		ft_strlcat(
			cmd_path, cmd_name, ft_strlen(cmd_path) + ft_strlen(cmd_name) + 1
			);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path_var_dir++;
	}
	return (NULL);
}
