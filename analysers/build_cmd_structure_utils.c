/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:06:52 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 02:35:50 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_through_quotes(char *line, char **new_line, int *i, int *j)
{
	if (line[*i] == '\'' && ft_strchr(line + *i + 1, '\''))
	{
		(*new_line)[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != '\'')
			(*new_line)[(*j)++] = line[(*i)++];
	}
	if (line[*i] == '\"' && ft_strchr(line + *i + 1, '\"'))
	{
		(*new_line)[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != '\"')
			(*new_line)[(*j)++] = line[(*i)++];
	}
}

t_cmd	*ft_split_to_cmd_lst(char *line, char delimiter)
{
	char	**phrases;
	t_cmd	*lst;
	int		i;

	phrases = ft_split(line, delimiter);
	lst = NULL;
	i = 0;
	while (phrases[i])
	{
		ft_cmd_addback(&lst, ft_cmdnew(ft_strdup(phrases[i])));
		i++;
	}
	ft_clear_array(phrases);
	return (lst);
}

static void	pass_through_quotes(char *str, size_t *i, size_t *size)
{
	if (str[*i] == '\'' && ft_strchr(str + *i + 1, '\''))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\'') - str - *i;
		*i = ft_strchr(str + *i + 1, '\'') - str;
	}
	if (str[*i] == '\"' && ft_strchr(str + *i + 1, '\"'))
	{
		if (size)
			*size += ft_strchr(str + *i + 1, '\"') - str - *i;
		*i = ft_strchr(str + *i + 1, '\"') - str;
	}
}

size_t	ft_new_line_size(char *str, int mode)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (str[i])
	{
		pass_through_quotes(str, &i, &size);
		if (str[i] == '>' * (mode == O_REDIR) + '<' * (mode == I_REDIR))
		{
			i++;
			if (str[i] == '>' * (mode == O_REDIR) + '<' * (mode == I_REDIR))
				i++;
			while (str[i] && !ft_isspace(str[i]) && !ft_isredirect(str[i]))
			{
				pass_through_quotes(str, &i, NULL);
				i++;
			}
			if (str[i] == '>' * (mode == O_REDIR) + '<' * (mode == I_REDIR))
				continue ;
		}
		i++;
		size++;
	}
	return (size);
}