/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:00:23 by asoler            #+#    #+#             */
/*   Updated: 2022/12/24 02:03:06 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_file_name(char *delimiter)
{
	char	*file_name;
	char	*aux;

	file_name = ft_strdup(delimiter);
	while (!access(file_name, F_OK))
	{
		aux = ft_strjoin(file_name, "x");
		free(file_name);
		file_name = ft_strdup(aux);
		free(aux);
	}
	return (file_name);
}

void	treat_empty_line(int fd)
{
	char	*endl;

	endl = calloc(sizeof(char), 2);
	endl[0] = '\n';
	ft_putstr_fd(endl, fd);
	free(endl);
}

void	heredoc_readline(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		line = readline("> ");
		if (!*line)
		{
			treat_empty_line(fd);
			continue ;
		}
		if (ft_strlen(delimiter) == ft_strlen(line) && \
			!ft_strncmp(delimiter, line, ft_strlen(line)))
			break ;
		ft_putendl_fd(line, fd);
	}
	free(line);
}

char	*heredoc(t_file *lst)
{
	char	*file_name;
	char	*buf;
	int		pipe_fd[2];
	int		fd;
	int		status;
	int		pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		heredoc_readline(lst->name, pipe_fd[1]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		exit(0);
		// builtin_exit();
	}
	else
	{
		file_name = find_file_name(lst->name);
		fd = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
		close(pipe_fd[1]);
		buf = get_next_line(pipe_fd[0]);
		while (buf)
		{
			write(fd, buf, ft_strlen(buf));
			free(buf);
			buf = get_next_line(pipe_fd[0]);
		}
		close(pipe_fd[0]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			//usar variavel global para exit code
			close(fd);
			WTERMSIG(status);
			return(NULL);
		}
	}
	close(fd);
	return (file_name);
}
