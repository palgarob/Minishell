/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:31:42 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/27 16:50:01 by pepaloma         ###   ########.fr       */
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

char	*ft_getenv(char *var_name)
{
	char	*value;

	value = getenv(var_name);
	if (!value)
	{
		value = (char *)malloc(sizeof(char) * 1);
		if (!value)
			return (perror(0), NULL);
		*value = 0;
	}
	value = ft_strdup(value);
	if (!value)
		return (perror(0), NULL);
	return (value);
}

int	trim_quotes(char **args)
{
	int		j;
	int		quote;
	
	j = -1;
	while ((*args)[++j])
	{
		if ((*args)[j] == '"' || (*args)[j] == '\'')
		{
			quote = (*args)[j];
			ft_strins(args, j, j + 1, "");
			while ((*args)[j] != quote)
				j++;
			ft_strins(args, j, j + 1, "");
		}
	}
	return (0);
}

char	**get_path_var(void)
{
	char	**path_var;

	path_var = ft_split(getenv("PATH"), ':');
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
