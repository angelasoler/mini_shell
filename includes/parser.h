/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:29:26 by asoler            #+#    #+#             */
/*   Updated: 2022/12/30 17:29:16 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_file
{
	char			*name;
	char			*hd_file;
	int				type;
	int				fd;
	int				hd_pid;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			*line;
	char			*exec_cmd;
	char			**args;
	int				type;
	int				index;
	t_file			*infiles;
	t_file			*outfiles;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

char	*parse_promt(void);

t_cmd	*ft_split_to_cmd_lst(char *line, char delimiter);
size_t	ft_new_line_size(char *str, int mode);
void	get_cmd_attributes(t_cmd **cmd);

t_file	*ft_filenew(char *name, int type);
t_cmd	*ft_cmdnew(char *phrase);
void	ft_file_addback(t_file **lst, t_file *new);
void	ft_cmd_addback(t_cmd **lst, t_cmd *new);
void	ft_filedelone(t_file *file, void (*del)(void *));
void	ft_fileclear(t_file **file, void (*del)(void *));
void	ft_cmddelone(t_cmd *cmd, void (*del)(void *));
void	ft_cmdclear(t_cmd **lst, void (*del)(void *));
void	ft_clear_array(char **array);
void	print_file_lst(t_file *lst);
void	print_cmd_lst(t_cmd *lst);
void	print_array_args(char **args);

char	*ft_worddup(char *s1, const char *delimiters);
void	copy_through_quotes(char *s, char **new_s, int *i, int *j);
void	pass_through_quotes(char *str, size_t *i, size_t *size);
char	**ft_split_but_through_quotes(char const *s, char delimiter);
int		verify_operators(char *line, char op);
void	trim_args(t_cmd **cmd, char *quotes);
void	trim_file_names(t_file **lst, char *quotes);

#endif