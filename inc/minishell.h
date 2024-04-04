/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/04 18:00:12 by incalero         ###   ########.fr       */
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
	struct s_command	*first_command;
	int					input;
	bool				close_in;
	int					output;
	bool				close_out;
	int					pipe_end[2];
	bool				close_pipe;
	char				**arguments;
	char				**path_var;
	char				**env_mini;
	struct s_command	*command;
}	t_command;

/*CLEAR_COMMANDS*/

void		close_pipes(t_command command);
void		clear_commands(t_command command);

/*EXEC_COMMANDS*/

pid_t		exec_commands(t_command command);

/*EXPAND_PAREMETERS*/

int			access_values(char **split_line);

/*FT_BUILTS_A*/

int			ft_export(t_command command);
int			ft_unset(t_command command);
char		**ft_dell(char **envcy, char **env_mini, int var_nbr);
char		**ft_dell_var(t_command command, char *var);
char		**ft_add_var(t_command command, char *var);
int			ft_change_var (t_command command);

/*FT_BUILTS*/

int			ft_echo(t_command command);
int			ft_env(t_command command);
int			ft_exit(t_command command);
int			ft_pwd(void);

/*FT_BUILTS_CD*/

int 		ft_directory_cmp(void);
int			ft_change_directory(const char *directory);
int			ft_cd (t_command command);

/*FT_INIT_COMMANDS*/

int			init_commands(t_command *command, char **split_line);

/*MINISHELL*/

int 		ft_case(t_command command);
int			main(int argc, char *argv[], char **env);
char		**ft_get_env(char **env);
void		ft_free_array(char **s);

/*PARSE_LINE*/

char		**parse_line(char *line);

/*UTILS*/

bool		is_metachar(char c);
char		*ft_getenv(char *var_name);
int			trim_quotes(char **args);
char		**get_path_var(void);
char		*get_cmd_path(char **path_var_dir, char *cmd_name);

#endif
