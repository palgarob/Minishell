/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/14 21:40:43 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt(void)
{
	static char			*line;

//	sig_handling();
	if (line)
		free(line);	
	line = readline("$ ");
	if (!line)
		ft_error(ERROR_RL, 0, 0, 0);
	if (*line == 'e')
		exit(1);
	if (*line)
		add_history(line);
	
}

int	main(void)
{
	while (1)
		prompt();
	return (0);
}
