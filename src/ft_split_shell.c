/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:02:43 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 02:59:43 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* En casos como una comilla pegada a palabras en posicion inesperada como:
"Pongo una comilla aqui' pero no la cierro" la funcion se piensa que
forma parte del final de esa palabra. No se si gestionar esto o no. Tampoco
creo que funcione bien si hay dos comillas pegadas de diferentes scopes*/

#include "minishell.h"

static int	stract_operator(char *line, char ***split_ptr)
{
	int		position;
	char	*arg;

	position = 1;
	if (*line == '<' || *line == '>')
	{
		if (line[position] == *line)
			position += 1;
	}
	arg = ft_substr(line, 0, position);
	if (!arg)
		return (perror(0), 0);
	if (ft_splitadd(arg, split_ptr))
		return (free(arg), 0);
	return (position);
}

static int	stract_argument(char *line, char ***split_ptr)
{
	int		position;
	char	*arg;
	int		quote;

	position = 0;
	while (!is_metachar(line[position]) && line[position] != 32
			&& line[position])
	{
		if (line[position] == '"' || line[position] == '\'')
		{
			quote = line[position++];
			while (line[position] != quote)
				if (!line[position++])
					return (perror("Unclosed quotes"), 0);
		}
		position++;
	}
	arg = ft_substr(line, 0, position);
	if (!arg)
		return (perror(0), 0);
	if (ft_splitadd(arg, split_ptr))
		return (free(arg), 0);
	return (position);
}

char	**ft_split_shell(char *line)
{
	char	**split;
	int		position;

	split = (char **)malloc(sizeof(char *) * 1);
	*split = NULL;
	while (*line)
	{
		if (*line == ' ')
			line++;
		else
		{
			if (is_metachar(*line))
				position = stract_operator(line, &split);
			else
				position = stract_argument(line, &split);
			if (!position)
				return (ft_splitfree(split), NULL);
			line += position;
		}
	}
	return (split);
}

/* int	main(void)
{
	char	*str = "i i";
	char	**split;

	split = ft_split_shell(str);
	if (!split)
	{
		printf("HOOLLLA");
		exit(0);
	}
	while (*split)
		ft_printf("%s\n", *(split++));
	return (0);
} */
