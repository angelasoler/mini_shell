/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:00:23 by asoler            #+#    #+#             */
/*   Updated: 2023/01/03 01:06:37 by asoler           ###   ########.fr       */
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

char	*fork_hd(t_file *lst, char **hd_file_name, int hd_file_fd)
{
	int		status;

	lst->hd_pid = fork();
	hd_sighandler(lst->hd_pid);
	if (lst->hd_pid == 0)
	{
		heredoc_readline(lst->name, hd_file_fd);
		close(hd_file_fd);
		free(*hd_file_name);
		return (NULL);
	}
	waitpid(lst->hd_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(hd_file_fd);
		unlink(*hd_file_name);
		ft_printf("\n");
		free(*hd_file_name);
		g_exit_code = 130;
		return (NULL);
	}
	close(hd_file_fd);
	return (*hd_file_name);
}

char	*heredoc(t_file *lst)
{
	char	*hd_file_name;
	int		hd_file_fd;

	if (!lst->name)
		return (NULL);
	hd_file_name = find_file_name(lst->name);
	hd_file_fd = open(hd_file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (!fork_hd(lst, &hd_file_name, hd_file_fd))
		return (NULL);
	g_exit_code = 0;
	return (hd_file_name);
}
