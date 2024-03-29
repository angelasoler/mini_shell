/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:57:04 by asoler            #+#    #+#             */
/*   Updated: 2023/01/22 05:48:04 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "parser.h"
# include "executer.h"
# include "environment.h"
# define MINISHELL_H

# define I_REDIR 1
# define HERE_DOC 2
# define O_REDIR 3
# define APPEND 4
# define BUILTIN 6

extern int	g_exit_code;

typedef struct s_data
{
	char	*line;
	char	**path;
	char	**envp;
	int		exit_code;
	t_exec	exec;
	t_cmd	*cmds;
	t_env	**hash_table;
}	t_data;

void	sig_handler(int pid);
void	chld_sighandler(int pid);
void	hd_sighandler(int pid);

void	prompt(t_data *data);

int		exec_builtin(t_data *data, t_cmd *node, int is_single);
void	builtin_exit(t_data *data, char **exit_code);
void	builtin_cd(t_data *data, char *path, t_cmd *node);
void	builtin_env(t_data *data, int export, int single);
int		builtin_unset(t_data *data, char **args);
int		builtin_export(t_data *data, char **args, int is_single);
int		builtin_echo(char **args);
int		valid_env_var(char *env);
int		*handle_single_builtins_redir(t_data *data, t_cmd *node);

t_cmd	*get_file_structures(t_data *data);

t_env	*get_env_var(t_data *data, char *key);
void	alloc_env_hash(char **envp, t_data *data);
void	create_replace_var(t_data *data, char *arg);
void	set_exec_paths(t_data *data);
void	set_envp(t_data *data);
void	free_hash_table(t_data *data);
int		hash_table_delete(t_data *data, char *key);
int		hash_table_insert(t_data *data, char *env);

void	executer(t_data *data);
int		ft_exec(t_data *data, t_cmd *node);
int		verify_cmd(char **path, t_cmd *node);
int		wait_and_free( t_data *data);

int		dup_fds(t_data *data, t_cmd *node);
int		init_fds(t_data *data);
void	close_file_fds(t_cmd *node);
void	close_fds(t_data *data);
void	free_fds(t_data *data, int n_cmds);
void	free_and_unlink_hd_files(t_data *data);

char	*heredoc(t_file *lst);

void	expansions(t_data data, t_cmd **cmds);
void	tilde_expansion(t_data data, char **s);
void	env_var_expansion(t_data data, char **s);
char	*ft_strsubstitute(char *str, char *del, char *insert, int pos);
char	*ft_strcpy_until(char *str, char *delimiter);

#endif
