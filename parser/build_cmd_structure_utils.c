/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:06:52 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/24 19:26:18 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
