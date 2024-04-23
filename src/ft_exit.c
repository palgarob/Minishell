/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:27:17 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/23 21:25:44 by pepaloma         ###   ########.fr       */
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

unsigned char	ft_atoc(char *str)
{
	int	i;

	i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == '\n')
	{
		i++;
		str++;
	}
	str += i;
	if (*str == '-')
		return (get_number((char *)str + 1) * -1);
	if (*str == '+')
		return (get_number((char *)str + 1));
	return (get_number((char *)str));
}

bool	is_numeric(char *arguments)
{
	int				i;

	i = 0;
	while (arguments[i] == ' ' || arguments[i] == '\t' || arguments[i] == '\v'
		|| arguments[i] == '\f' || arguments[i] == '\r' || arguments[i] == '\n')
		i++;
	if (arguments[i] == '-'
		|| arguments[i] == '+')
		i++;
	while (arguments[i])
	{
		if (!ft_isdigit(arguments[i++]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, arguments,
				ft_strlen(arguments));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			return (false);
		}
	}
	return (true);
}

int	ft_exit(t_shell shell)
{
	unsigned char	status;

	status = 0;
	printf("exit\n");
	if (shell.first_command.arguments[1])
	{
		if (is_numeric(shell.first_command.arguments[1]))
		{
			if (shell.first_command.arguments[2])
			{
				write(STDERR_FILENO, "exit: too many arguments\n", 25);
				return (1);
			}
			status = ft_atoc(shell.first_command.arguments[1]);
		}
		else
			status = 255;
	}
	ft_splitfree(shell.mini_env);
	ft_splitfree(shell.first_command.arguments);
	rl_clear_history();
	exit(status);
	return (0);
}
