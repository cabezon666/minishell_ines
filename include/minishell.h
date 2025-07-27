/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:00:35 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/07/27 18:37:44 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# define _GNU_SOURCE

# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define MAX_CMD_LENGTH 1024
# define MAX_ARGS 100

# define INPUT_REDIR 1
# define HERE_DOC 2
# define OUTPUT_REDIR 4
# define APPEND 8

extern int			g_signal;

typedef enum e_parse_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
}					t_parse_state;

typedef enum e_redir_type
{
	NO_REDIR,
	IN_REDIR,
	OUT_REDIR,
	APPEND_REDIR,
	HEREDOC_REDIR,
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*first_cmd;

	char			**args;
	char			*full_cmd;
	char			**split_cmd;
	char			*from_file;
	char			*to_file;
	char			*heredoc_delim;
	t_redir			*redirec;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_mini
{
	t_cmd			*cmd;
	char			**env;
	char			**path;
	int				fd;
	int				signal_status;
	int				ready;
	int				exit_code;
}					t_mini;

typedef struct s_pipe_data
{
	t_mini			*mini;
	t_cmd			*current;
	char			*input;
	int				prev_pipe_in;
}					t_pipe_data;

typedef struct s_child_data
{
	t_mini			*mini;
	t_cmd			*current;
	char			*input;
	int				prev_pipe_in;
}					t_child_data;

typedef struct s_parse_data
{
	int				i;
	int				arg_count;
	t_parse_state	state;
	int				start;
	int				error_flag;
}					t_parse_data;

/*====== BUILTINS ========*/

int					ft_cd(t_mini *mini, char **args);
int					update_env_var(t_mini *mini, const char *var,
						const char *value);

int					ft_echo(t_mini *mini, char **arg);

int					ft_env(t_mini *mini, char **args);

void				ft_exit(t_mini *mini, char **args, char *input);

int					ft_export(t_mini *mini, char **args);
int					export_no_args(t_mini *mini);
int					add_to_env(t_mini *mini, char *arg);
int					find_env_var(char **env, const char *name);
char				*ft_strjoin3(const char *s1, const char *s2,
						const char *s3);

int					ft_pwd(t_mini *mini);

int					ft_unset(t_mini *mini, char **args);
char				*get_env_value(char **env, const char *var_name);

/*====== EXECUTE ========*/

char				*expand_env_vars(t_mini *mini, char *str);
char				*env_value(t_mini *mini, char *var_name);
void				expand_cmd_args(t_mini *mini, t_cmd *cmd);

int					execute(t_mini *mini, char *input);
void				execute_child_process(t_child_data *data, int *pipes);
int					execute_single_builtin(t_mini *mini, char *input);

int					handle_redirections(t_cmd *cmd);
int					handle_heredoc(char *delimiter);

int					is_builtin(t_mini *mini);
int					execute_builtin(t_mini *mini, t_cmd *cmd, char *input);
int					is_state_builtin(const char *cmd);

char				*get_cmd_path(char **path_dirs, char *cmd);
void				clean_child_exit(t_mini *mini, char *input, int code);

/*====== MAIN ===========*/

void				init_mini(t_mini *mini, int argc, char **argv, char **envp);
char				**copy_env(char **envp);
char				**get_path(char **envp);

/*====== PARSER =========*/

void				parser(t_mini *mini, char *line);
char				**split_args_quote_aware(t_mini *mini, char *cmd_str);
char				*process_arg(t_mini *mini, char *raw_arg, int len);
char	*concatenate_sections(t_mini *mini, char *raw_arg, int len);
		// ADD THIS LINE
int					validate_quotes(const char *line);

void				setup_signals(void);

void				process_redir(t_cmd *cmd);

t_cmd				*create_command_structure(char **commands, t_mini *mini);
t_cmd				*alloc_cmd_and_set_full(char *command);
int					handle_split_cmd(t_cmd *cmd, t_mini *mini, char *command);
int					handle_first_cmd(t_cmd *cmd);
int					build_command_list(char **commands, t_mini *mini,
						t_cmd **head, t_cmd **current);

char				**split_commands(char *line);

/*====== UTILS ===========*/

int					error_message(char *context);
int					ft_isspace(char c);
int					ft_strisspace(const char *str);
char				*ft_strjoin_char(char *s1, char c);

void				free_list(char ***path);
void				free_list_cmd(t_cmd **cmd);
void				free_redir_list(t_redir **redir);
void				free_per_command(t_mini *mini);
void				free_mini(t_mini *mini);
void				cleanup(t_mini *mini, char **input);

#endif
