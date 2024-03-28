/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ioflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:22:49 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/28 11:29:38 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_ioflow(t_ioflow ioflow)
{
	if (ioflow.close_in)
		close(ioflow.input);
	if (ioflow.close_out)
		close(ioflow.output);
	if (ioflow.close_pipe)
	{
		close(ioflow.pipe_end[0]);
		close(ioflow.pipe_end[1]);
	}
}
