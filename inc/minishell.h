/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/12 11:46:39 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

void	builtins(t_command command);
void	ft_export(t_command command);
void	ft_unset(t_command command);
void	ft_echo(t_command command);
void	ft_cd(t_command command);
void	ft_env(t_command command);
void	ft_pwd(void);
void	ft_exit(t_command command);

size_t ft_str_equal_len(char *s);
int ft_is_equal (char *s);
int ft_var_is_ok(char *s);
int ft_var_exist(t_command command , char *var);
void ft_add_var (t_command command, char *var);
char **ft_dell_var(t_command command, char *var);

bool	is_metachar(char c);
char	*ft_getenv(char *var_name, char **mini_env);
char	*get_cmd_path(char *cmd_name, char **mini_env);
int		trim_quotes(char **split_line);

void	clear_commands(t_command command);
void	close_pipes(t_command command);

#endif
