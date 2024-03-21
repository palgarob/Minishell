/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/21 15:11:41 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_T
# define MINISHELL_T

# include <readline/readline.h>
# include <signal.h>

# include "../libft-improved/inc/libft.h"

# define ERR_PARSE "Parse error"
# define ERR_SYNTAX "Syntax error"

typedef struct s_ioflow
{
	int					input;
	bool				close_in;
	int					output;
	bool				close_out;
	int					pipe_end[2];
	bool				close_pipe;
	char				**command;
	struct s_ioflow		*ioflow;
}	t_ioflow;

extern int	current_signal;

void	sig_handling(void);
char	**parse(char *line);
char	**ft_split_shell(char *line);
bool	is_metachar(char c);
char	*ft_getenv(char *var_name);
int		trim_quotes(char **args);
int 	access_values(char **args);

#endif
