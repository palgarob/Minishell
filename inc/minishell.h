/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incalero <incalero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:23:30 by pepaloma          #+#    #+#             */
/*   Updated: 2024/04/10 11:10:40 by incalero         ###   ########.fr       */
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

/*FT_BUILTS_A*/

int			ft_var_exist(t_command *command, char *var);
int 		ft_is_equal (char *s);
size_t		ft_str_equal_len(char *s);
char		**ft_env_mini_order(t_shell *shell);
void 		ft_export_env(t_shell *shell);
int			ft_export(t_shell *shell);
void		ft_unset(t_shell *shell);
char		**ft_dell(char **envcy, char **env_mini, int var_nbr);
char		**ft_dell_var(t_shell *shell, char *var);
void		ft_add_var(t_shell *shell, char *var);
int			ft_change_var (t_command command);

/*FT_BUILTS*/

int			ft_echo(t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_exit(t_shell *shell);
int			ft_pwd(void);

/*FT_BUILTS_CD*/

int 		ft_directory_cmp(void);
int			ft_change_directory(const char *directory);
int			ft_cd (t_shell *shell);

/*FT_INIT_COMMANDS*/

int			init_commands(t_command *command, char **split_line);

/*MINISHELL*/

void 		ft_case(t_shell *shell);
int			main(int argc, char *argv[], char **env);
char		**ft_get_env(char **env);
void		ft_free_array(char **s);

/*PARSE_LINE*/

char		**parse_line(char *line);

/*UTILS*/

bool		is_metachar(char c);
char		*ft_getenv(char *var_name);
char		***ft_get_env_var(char **env);
int			trim_quotes(char **args);
char		**get_path_var(void);
char		*get_cmd_path(char **path_var_dir, char *cmd_name);

/*EXEC_COMMANDS*/
void 		ft_only_local_var(t_command *command);
int 		ft_is_local_var(t_command *command);
int 		ft_command_no_found(t_shell *shell);
int 		ft_is_command (t_shell *shell);

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
