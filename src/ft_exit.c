/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/22 11:02:27 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	get_number(char *s)
{
	unsigned char	n;

	n = 0;
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n);
}

static int	count_spaces(char *s)
{
	int	i;

	i = 0;
	while (*s == ' ' || *s == '\t' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == '\n')
	{
		i++;
		s++;
	}
	return (i);
}

unsigned char	ft_atoc(char *str)
{
	str += count_spaces((char *)str);
	if (*str == '-')
		return (get_number((char *)str + 1) * -1);
	if (*str == '+')
		return (get_number((char *)str + 1));
	return (get_number((char *)str));
}

unsigned char	exit_with_arg(char **arguments)
{
	int				i;

	i = count_spaces(arguments[1]);
	if (arguments[1][i] == '-'
		|| arguments[1][i] == '+')
		i++;
	while (arguments[1][i])
	{
		if (!ft_isdigit(arguments[1][i++]))
		{
			return (255);
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, arguments[1],
				ft_strlen(arguments[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			break ;
		}
	}
	return (ft_atoc(arguments[1]));
}

int	ft_exit(t_shell shell)
{
	unsigned char	status;

	status = 0;
	printf("exit\n");
	if (shell.first_command.arguments[1])
	{
		if (shell.first_command.arguments[2])
		{
			write(STDERR_FILENO, "exit: too many arguments\n", 25);
			return (1);
		}
		status = exit_with_arg(shell.first_command.arguments);
	}
	ft_splitfree(shell.mini_env);
	ft_splitfree(shell.first_command.arguments);
	rl_clear_history();
	exit(status);
	return (0);
}
