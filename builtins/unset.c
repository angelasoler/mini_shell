/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:21:51 by asoler            #+#    #+#             */
/*   Updated: 2023/01/01 16:58:34 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_var(t_env *node, char *key, size_t key_len)
{
	t_env	*prev;

	prev = NULL;
	while (node)
	{
		if (!ft_strncmp(key, node->key, key_len) && \
			key_len == ft_strlen(node->key))
		{
			if (prev && node->next)
				prev->next = node->next;
			if (!node->next)
				prev->next = NULL;
			ft_envdelone(node, free);
			break ;
		}
		prev = node;
		node = node->next;
	}
}

int	builtin_unset(t_data *data, char **args)
{
	unsigned int	index;
	t_env			*node;
	int				i;

	i = 1;
	if (!args[i])
		return (1);
	while (args[i])
	{
		index = hash(args[i]);
		node = data->hash_table[index];
		if (!identifier_verification(args[i]))
		{
			i++;
			continue ;
		}
		remove_var(node, args[i], ft_strlen(args[i]));
		i++;
	}
	return (0);
}
