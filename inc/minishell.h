/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepaloma <pepaloma@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/05 13:48:30 by pepaloma         ###   ########.fr       */
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
	struct s_shell		*shell;
	int					input;
	bool				close_in;
	int					output;
	bool				close_out;
	int					pipe_end[2];
	bool				close_pipe;
	char				**arguments;
	struct s_command	*piped_command;
}	t_command;

typedef struct s_shell
{
	struct s_command	first_command;
	char				**mini_env;
	int					les;
	bool				rm_here_doc;
}	t_shell;

char	**parse_line(char *line);
int		init_commands(t_shell *shell, char **args);
int		redirect_io(t_command *command, char **split_line);
int		expand_parameters(char **split_line, bool ignore_quotes, char **mini_env, int les);
pid_t	exec_commands(t_command command);

// Functions in utils.c
bool	is_metachar(char c);
char	*ft_getenv(char *var_name, char **mini_env);
char	*get_cmd_path(char *cmd_name, char **mini_env);
int		trim_quotes(char **split_line);

void	clear_commands(t_command command);
void	close_pipes(t_command command);

#endif
