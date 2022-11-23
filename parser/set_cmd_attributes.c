/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:36:35 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/23 14:53:21 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_absolute_path(char *arg)
{
	if (*arg == '/')
	{
		if (verify_access(arg, F_OK))
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	get_cmd_type(char *line)
{
	char	*trimed_line;
	int		type;

	trimed_line = ft_strtrim(line, " \f\n\r\t\v");
	if (!trimed_line)
		return (0);
	type = is_absolute_path(trimed_line);
	if ((ft_strncmp(trimed_line, "echo", 4) == 0)
		|| (ft_strncmp(trimed_line, "cd", 2) == 0)
		|| (ft_strncmp(trimed_line, "pwd", 3) == 0)
		|| (ft_strncmp(trimed_line, "export", 6) == 0)
		|| (ft_strncmp(trimed_line, "unset", 5) == 0)
		|| (ft_strncmp(trimed_line, "env", 3) == 0)
		|| (ft_strncmp(trimed_line, "exit", 4) == 0))
		type = BUILTIN;
	else if (type == 1)
		type = ABSPATH;
	else if (type == -1)
		type = 0;
	free(trimed_line);
	return (type);
}

void	get_cmd_attributes(t_cmd **cmd)
{
	(*cmd)->args = ft_split_but_through_quotes((*cmd)->line, ' ');
	if (*(*cmd)->args)
	{
		(*cmd)->type = get_cmd_type((*cmd)->args[0]);
		(*cmd)->exec_cmd = ft_strdup((*cmd)->args[0]);
	}
	else
	{
		(*cmd)->type = 0;
		(*cmd)->exec_cmd = NULL;
	}
}
