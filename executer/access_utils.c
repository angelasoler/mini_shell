/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:21:37 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 19:22:29 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd_error(char *arg, int message)
{
	write(2, "bash: ", 6);
	ft_putstr_fd(arg, 2);
	if (!message)
		ft_putendl_fd(": No such file or directory", 2);
	else if (message == 2)
		ft_putendl_fd(": command not found", 2);
	else
		ft_putendl_fd(": Is a directory", 2);
}

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		if (mode == R_OK || mode == W_OK)
			ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

int	is_directory(char *path)
{
	struct stat	path_info;

	stat(path, &path_info);
	if (S_ISDIR(path_info.st_mode))
		return (1);
	return (0);
}

int	is_absolute_path(char *path)
{
	if (*path == '/')
	{
		if (is_directory(path))
			return (-1);
		if (verify_access(path, F_OK))
			return (1);
		else
			return (0);
	}
	return (2);
}

int	verify_cmd(char **path, t_cmd *node)
{
	char	*join_cmd;
	int		i;

	i = 0;
	if (!node->exec_cmd)
		return (0);
	while (path[i])
	{
		if (is_absolute_path(node->args[0]) <= 0)
			break ;
		else if (is_absolute_path(node->args[0]) == 1)
			return (1);
		join_cmd = ft_strjoin(path[i], node->args[0]);
		if (verify_access(join_cmd, F_OK))
		{
			free(node->exec_cmd);
			node->exec_cmd = join_cmd;
			return (1);
		}
		free(join_cmd);
		i++;
	}
	print_cmd_error(node->args[0], is_absolute_path(node->args[0]));
	return (0);
}
