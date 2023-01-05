/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:36:35 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/05 03:02:45 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_cmd_type(char *line)
{
	char	*trimed_line;
	int		type;

	type = 0;
	trimed_line = ft_strtrim(line, " \f\n\r\t\v");
	if (!trimed_line)
		return (0);
	if (!(ft_strncmp(trimed_line, "cd", 3))
		|| !(ft_strncmp(trimed_line, "export", 7))
		|| !(ft_strncmp(trimed_line, "unset", 6))
		|| !(ft_strncmp(trimed_line, "env", 5))
		|| !(ft_strncmp(trimed_line, "echo", 5))
		|| !(ft_strncmp(trimed_line, "exit", 7)))
		type = BUILTIN;
	else if (!ft_strncmp(trimed_line, "pwd", 4))
		type = -1;
	free(trimed_line);
	return (type);
}

char	**realloc_args(char **args)
{
	char	**new_staff;

	new_staff = ft_calloc(sizeof(char *), 2);
	new_staff[0] = ft_strdup(args[0]);
	free_and_count_array(args, free);
	return (new_staff);
}

void	copy_through_quotes(char *s, char **new_s, int *i, int *j)
{
	if (s[*i] == '\'' && ft_strchr(s + *i + 1, '\''))
	{
		(*new_s)[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != '\'')
			(*new_s)[(*j)++] = s[(*i)++];
	}
	if (s[*i] == '\"' && ft_strchr(s + *i + 1, '\"'))
	{
		(*new_s)[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != '\"')
			(*new_s)[(*j)++] = s[(*i)++];
	}
}

void	get_cmd_attributes(t_cmd **cmd)
{
	(*cmd)->args = ft_split_but_through_quotes((*cmd)->line, ' ');
	if (*(*cmd)->args)
	{
		(*cmd)->type = get_cmd_type((*cmd)->args[0]);
		(*cmd)->exec_cmd = ft_strdup((*cmd)->args[0]);
		if ((*cmd)->type < 0)
			(*cmd)->args = realloc_args((*cmd)->args);
	}
	else
	{
		(*cmd)->type = 0;
		(*cmd)->exec_cmd = NULL;
	}
}
