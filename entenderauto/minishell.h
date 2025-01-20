/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:40:50 by jlara-na          #+#    #+#             */
/*   Updated: 2025/01/20 14:09:33 by aurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------------------------------INCLUDE----------------------------------//

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "automata.h"

# include "lib/libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"

//-----------------------------------DEFINES----------------------------------//

extern int	g_signal_data;

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef ERROR
#  define ERROR 1
# endif

# ifndef CHILD
#  define CHILD 0
# endif

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef ARG_MAX
#  define ARG_MAX 4096
# endif

typedef enum e_pipe_fd
{
	READ_END,
	WRITE_END
}	t_pipe_fd;

# ifndef M_SHELL_PROMPT
#  define M_SHELL_PROMPT "$minishell:"
# endif

# ifndef MSG_BYE
#  define MSG_BYE "Bye!\n"
# endif

//-----------------------------DEFINING STRUCTURES----------------------------//

typedef struct s_shell
{
	t_automata	splitter;
	t_automata	expander;
	t_automata	tokenizer;
	t_tree		*token_tree;
	t_list		*enviroment;
	pid_t		last_pid;
	int			child;
	int			exit_status;
	char		*readline;
	char		**default_env;
	char		**path_var;
}	t_shell;

typedef struct s_token
{
	t_shell		*shell;
	int			append;
	char		*line;
	char		*cmd;
	char		**args;
	char		**infiles;
	char		**heredoc;
	char		**outfiles;
	int			last_outf_fd;
	int			last_inf_fd;
	void		*data;
}	t_token;

//Enviroment variable (name, value)
typedef struct s_var
{
	char		*name;
	char		*value;
}	t_var;

//----------------------------------FUNCTIONS---------------------------------//

//Enviroment funcions

void	import_env(t_shell	*shell, char **env);
void	add_new_var(t_list	*enviroment, t_var	*newvar);
t_bool	find_var(void *content, void *context);
char	*find_value(t_list	*env, char	*name);
t_var	*create_var(char *name, char *value);
void	update_default_env(t_shell	*shell);
char	**get_path_var(t_shell	*shell);

//Parsing functions

int		split_in_token_lines(t_shell	*shell);
void	tokenize_node(void	*token_ptr, void	*shell_ptr);


//Executing functions

void	exe_minishell_recursive(t_tree	*tree);
void	wait_childs(t_token	*token, int twice);
void	child_pipe_redir(t_tree *node, t_token *token, int pid, int fd[2]);
void	exe_comand_node(t_token	*token, int pid);
void	stdout_redirection(t_token	*token);
void	stdin_redirection(t_token	*token);
char	*do_heredoc(char *str, t_token	*token);
void	unlink_heredocs(void	*token_ptr, void	*shell_ptr);
void	stdin_stdout_reset(t_token	*token, int saved_std[2]);
void	exe_built_in_with_redirs(t_shell	*shell, t_token	*token);
int		is_built_in(char	*cmd);
int		exe_built_in(void	*data, void	*context);
void	exe_path_cmd(t_shell	*shell, t_token	*token);
void	exe_cmd_or_built(t_shell	*shell, t_token	*token);

//Built-in functions

int		built_in_cd(t_shell *shell, t_token	*token);
int		built_in_pwd(t_shell	*shell);
int		built_in_env(t_shell	*shell);
int		built_in_exit(t_shell	*shell, t_token	*token);
int		built_in_echo(t_token	*token);
int		built_in_unset(t_shell	*shell, t_token	*token);
int		built_in_export(t_shell *shell, t_token	*token);

//Utils

char	*generate_prompt(void);
void	free_env(t_shell	*shell);
void	set_sig_handler(void (handler)(int signum), int sigquit_status);
void	standard_handler(int signum);
void	heredoc_handler(int signum);

//----------------------------------ERROR MSG---------------------------------//

# define ERROR_EXIT 	"EXIT\n"

//-----------------------------------DEFINES----------------------------------//

# define CD_BUILT		"cd"
# define ECHO_BUILT		"echo"
# define ENV_BUILT		"env"
# define EXIT_BUILT		"exit"
# define EXPORT_BUILT	"export"
# define PWD_BUILT		"pwd"
# define UNSET_BUILT	"unset"
# define PIPE_LINE		"|"
# define ESCAPE_2		2
# define ESCAPE_126		126
# define ESCAPE_127		127


# endif
