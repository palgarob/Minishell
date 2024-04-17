/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/16 12:44:05 by incalero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft-improved/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# define ERR_PARSE "Parse error"
# define ERR_SYNTAX "Syntax error"

pid_t	wp; //Variable global

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

/* Program's main flow */
char	**parse_line(char *line);
int		init_commands(t_shell *shell, char **args);
int		redirect_io(t_command *command, char **split_line);
int		expand_parameters(char **split_line, bool ignore_quotes, char **mini_env, int les);
void	exec_commands(t_command command);

/* Builtin commands */
bool	is_builtin(char *cmd);
int		exec_builtin(t_command *command);
int		ft_echo(t_command *command);
int		ft_cd(t_command *command);
int		ft_pwd(void);
int		ft_exit(t_command *command);
int		ft_export(t_command *command);
int		ft_unset(t_command *command);
int		ft_env(t_command *command);

size_t	ft_str_equal_len(char *s);
int		ft_is_equal (char *s);
int		ft_var_is_ok(char *s);
int		ft_var_exist(t_command *command , char *var);
void	ft_add_var (t_command *command, char *var);
char	**ft_dell_var(t_command *command, char *var);
char	**ft_dell_oldpwd(t_shell *shell, char *var);
char 	**ft_dell(char **env_mini, char **envcpy, int var_nbr);

/* Auxiliary functions */
bool	is_metachar(char c);
char	*ft_getenv(char *var_name, char **mini_env);
char	*get_cmd_path(char *cmd_name, char **mini_env);
int		trim_quotes(char **split_line);

/* Clearing and freeing functions */
void	clear_commands(t_command command);
void	close_pipes(t_command command);

#endif
