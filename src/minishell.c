/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:22:50 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/16 23:08:36 by pepaloma         ###   ########.fr       */
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
		exit (1);
	if (*line)
		add_history(line);
	if (parse_line(line))
		
}

int	main(void)
{
	while (1)
		prompt();
	return (0);
}
