/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:03:59 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 00:59:34 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quote(char *str, char quote)
{
	int		i;
	size_t	len;
	char	*aux;

	i = 0;
	len = len_without_quotes(str, quote);
	if (len == ft_strlen(str))
		return (str);
	aux = ft_calloc(sizeof(char), len + 1);
	len = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			i++;
			continue ;
		}
		aux[len] = str[i];
		len++;
		i++;
	}
	free(str);
	return (aux);
}

char	*trim_and_free(char **arg, char *quote)
{
	char	*aux;
	char	*str;

	str = *arg;
	aux = ft_strtrim(str, quote);
	free(*arg);
	aux = remove_quote(aux, *quote);
	return (aux);
}

char	*treat_notquoted_arg(char *str)
{
	char	*aux;

	aux = str;
	if (*str != '\'')
	{
		aux = remove_quote(str, '\"');
		aux = remove_quote(aux, '\'');
	}
	return (aux);
}

void	trim_args(t_cmd **cmd, char *quotes)
{
	int		i;
	t_cmd	*node;

	i = 0;
	node = *cmd;
	while (node->args[i])
	{
		if (node->args[i][0] != *quotes)
		{
			if (*quotes == '\"')
				node->args[i] = treat_notquoted_arg(node->args[i]);
			i++;
			continue ;
		}
		if (!node->args[i][0])
			return ;
		node->args[i] = trim_and_free(&node->args[i], quotes);
		i++;
	}
}

void	trim_file_names(t_file **lst, char *quotes)
{
	t_file	*node;

	if (!*lst)
		return ;
	node = *lst;
	while (node)
	{
		if (*node->name != *quotes || !node->name)
		{
			if (*quotes == '\"' && node->name)
				node->name = treat_notquoted_arg(node->name);
			node = node->next;
			continue ;
		}
		node->name = trim_and_free(&node->name, quotes);
		node = node->next;
	}
}
