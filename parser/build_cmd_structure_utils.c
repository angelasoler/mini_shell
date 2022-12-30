/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:06:52 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/30 03:52:07 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_operators(char *line, char op)
{
	int	count;

	count = 0;
	if (*line == '|')
		return (0);
	while (*line)
	{
		if (*line != op && count < 3)
			count = 0;
		if (*line == op)
			count++;
		if ((count > 1 && op == '|') || count > 2)
			return (0);
		line++;
	}
	return (1);
}

void	trim_file_names(t_file **lst, char *quotes)
{
	t_file	*node;
	char	*aux;

	if (!*lst)
		return ;
	node = *lst;
	while (node)
	{
		aux = ft_strtrim(node->name, quotes);
		free(node->name);
		node->name = aux;
		node = node->next;
	}
}

t_cmd	*ft_split_to_cmd_lst(char *line, char delimiter)
{
	char	**phrases;
	t_cmd	*lst;
	int		i;

	phrases = ft_split_but_through_quotes(line, delimiter);
	lst = NULL;
	i = 0;
	while (phrases[i])
	{
		ft_cmd_addback(&lst, ft_cmdnew(ft_strdup(phrases[i])));
		i++;
	}
	ft_clear_array(phrases);
	if (!lst)
		ft_cmdclear(&lst, free);
	return (lst);
}

static void	pass_on_redirect_word(char *str, int mode, size_t *i, size_t *size)
{
	if (str[(*i)] == '>' * (mode == O_REDIR) + '<' * (mode == I_REDIR))
		(*i)++;
	while (str[(*i)] == ' ')
	{
		(*i)++;
		(*size)++;
	}
	while (str[(*i)] && !ft_isspace(str[(*i)]) && !ft_isredirect(str[(*i)]))
	{
		pass_through_quotes(str, i, NULL);
		(*i)++;
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
			pass_on_redirect_word(str, mode, &i, &size);
			if (!str[i])
				return (size);
			if (str[i] == '>' * (mode == O_REDIR) + '<' * (mode == I_REDIR))
				continue ;
		}
		i++;
		size++;
	}
	return (size);
}
