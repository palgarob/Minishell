/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/03/29 20:35:36 by pepaloma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_T
# define MINISHELL_T

# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

# include "../libft-improved/inc/libft.h"

# define ERR_PARSE "Parse error"
# define ERR_SYNTAX "Syntax error"

typedef struct s_command
{
	int					input;
	bool				close_in;
	int					output;
	bool				close_out;
	int					pipe_end[2];
	bool				close_pipe;
	char				**arguments;
	char				**path_var;
	struct s_command	*command;
}	t_command;

char	**parse_line(char *line);
int		init_commands(t_command *command, char **args);
void	exec_commands(t_command command);

// Functions in utils.c
bool	is_metachar(char c);
char	*ft_getenv(char *var_name);
int		trim_quotes(char **args);
char	**get_path_var(void);
char	*get_cmd_path(char **path_var_dir, char *cmd_name);

void	clear_commands(t_command command);
void	close_pipe(t_command command);

int		access_values(char **split_line);

#endif
