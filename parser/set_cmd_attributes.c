/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:36:35 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/30 01:32:08 by asoler           ###   ########.fr       */
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
	if ((ft_strncmp(trimed_line, "cd", 2) == 0)
		|| (ft_strncmp(trimed_line, "export", 6) == 0)
		|| (ft_strncmp(trimed_line, "unset", 5) == 0)
		|| (ft_strncmp(trimed_line, "env", 4) == 0)
		|| (ft_strncmp(trimed_line, "exit", 5) == 0))
		type = BUILTIN;
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

void	trim_args(t_cmd **cmd, char *quotes)
{
	int		i;
	t_cmd	*node;
	char	*aux;

	i = 0;
	node = *cmd;
	while (node->args[i])
	{
		aux = ft_strtrim(node->args[i], quotes);
		free(node->args[i]);
		node->args[i] = aux;
		i++;
	}
}
